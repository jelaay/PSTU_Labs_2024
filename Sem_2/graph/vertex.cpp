#include "vertex.h"
#include "edge.h"
#include "graph.h"

#include <QVector>

//создаем вершину. Получаем указатель и индекс
Vertex::Vertex(Graph *graph, int index) : graph(graph){
    setFlag(ItemIsMovable); //возможность двигать
    setFlag(ItemSendsGeometryChanges); //
    setCacheMode(DeviceCoordinateCache); //прорисовка
    setZValue(-1);
    vertexIndex = index; //номер вершины
    degree = 0; //количество ребер
    color = "white";
    name = "";
}

Vertex::~Vertex(){ //удаляем вершину, ребра и и обнуляем количество ребер
    clearEdge();
    degree = 0;
}

//возвращаем цвет вершины
QString Vertex::getColor(){ return this -> color;}

void Vertex::setColor(QString color){ //устанавливает цвет вершины и обновляет поле
    this -> color = color;
    qApp->processEvents();
    update();
}
//возвращает имя вершины
QString Vertex::getName(){return name;}

//устанавливает имя вершины
void Vertex::setName(QString name){ this -> name = name; }

void Vertex::addEdge(Edge *edge){ //связываем вершины и добавляем ребро в список ребер + увеличиваем количество ребер
    edgeList << edge;
    edge -> tuneEdge();
    degree ++;
}

//возвращаем количнство ребер для заданной вершины
QVector<Edge *> Vertex::getEdges() const{return edgeList;}

//рассчет положения вершин на сцене, чтобы избежать выхода за пределы, перехваты курсором, зависания итд
void Vertex::calculateForces(){
    //проверяем - есть ли вершина на сцене и не мешает ли ей другая вершина
    if(!scene() || scene()->mouseGrabberItem() == this){
        newPos = pos();
        return;
    }
    qreal xvel = 0; //храним Х и Y. Нам в дальнейшем нельзя допустить, чтобы вершины накладывались друг на друга
    qreal yvel = 0;
    //получаем список элементов на сцене
    const QList<QGraphicsItem *> items = scene()->items();
    for(QGraphicsItem *item : items){ //перебираем все эти элементы
        Vertex *temp = qgraphicsitem_cast<Vertex *>(item); //присваиваем текущий элемент пока не найдем вершину
        if(!temp){continue;}

        //считаем насколько надо сдвинуть вершину от другой, когда они касаются друг друга
        QPointF vec = mapToItem(temp, 0, 0); //начальна вершина и ее координаты
        qreal dx = vec.x(); //извлекаем горизонтальную ось
        qreal dy = vec.y(); //извлекаем вертикальную ось
        double l = 4 * (dx * dx + dy * dy); //рассчитываем расстояние
        if(l > 0 && l < 1000){
            xvel += (dx * 250) / l; //отводим другую вершину на полученное значение
            yvel += (dy * 250) / l;
        }
    }
    if(qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1){ //делаем объекты недвижимыми
        xvel = yvel = 0;
    }
    //Получаем ограничивающий границы сцены.
    //Считаем новую позицию, добавляя вычисленные значения отвода к текущей позиции.
    //Ограничиваем новую позицию границами сцены с 10-пиксельным отступом по бокам и снизу, и 145-пиксельным отступом сверху (учитываем менюшку).
    QRectF sceneRect = scene()->sceneRect();
    newPos = pos() + QPointF(xvel, yvel);
    newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + 20), sceneRect.right() - 20));
    newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + 145), sceneRect.bottom() - 20));
}

//проверяем новую позицию вершины
bool Vertex::advancePosition(){
    if(newPos == pos()){return false;} //если новая = старая, то не смещаем
    setPos(newPos); //устанавливаем новую позицию и перемещаем
    return true; //если переместили - возвращаем true
}

int Vertex::getDegree(){return degree;} //возвращаем количество ребер

int Vertex::getIndex(){return vertexIndex;} //возвращаем индекс ребра

void Vertex::setIndex(int index){ //присваисваем новый индекс и обновляем сцену
    vertexIndex = index;
    qApp->processEvents();
    update();
}

//проверяем - можно ли соединить ребро с вершиной Б
bool Vertex::pathExist(int secondV){
    for(Edge *temp : edgeList){ //перебираем список ребер
        if(temp -> secondVertex() -> getIndex() == secondV){ //если ребро ведет к вершине Б
            return true; //можно
        }
    }
    return false; //нельзя
}

//устанавливаем новую позицию для вершины
void Vertex::setPosition(double xvel, double yvel){
    //считываем границы сцены
    QRectF sceneRect = scene()->sceneRect();
    //к текущей позиции вершины добавляются новые координаты и смещаем, учитывая менюшку
    newPos = pos() + QPointF(xvel, yvel);
    newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + 10), sceneRect.right() - 10));
    newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + 145), sceneRect.bottom() - 10));
}

//вставляем новое ребро от вершины с весом
void Vertex::insertEdge(int secondV, double weight){
    //получаем список элементов на сцене
    const QList<QGraphicsItem *> items = scene()->items();
    for(QGraphicsItem *item : items){ //перебираем их и ищем вершину
        Vertex *temp = qgraphicsitem_cast<Vertex *>(item);
        if(!temp){continue;} //если не вершина, то продолжаем искать
        if(temp->getIndex() == secondV){ //если индекс вершины совпадает с той, у которой вставляем
            Edge *edge = new Edge(this, temp, weight);  //создаем новое ребро
            edgeList.append(edge); //добавляем его в список
            return;
        }
    }
}

//обновляем вес ребра вершины
void Vertex::updateWeight(int secondV, double weight){
    for(Edge *temp : edgeList){ //перебираем список ребер
        if(temp -> secondVertex() -> getIndex() == secondV){ //если находим нужную вершину
            temp -> setWeight(weight); //обновляем у нее вес
        }
    }
}

//удаляем ребро у вершины
void Vertex::eraseEdge(int secondV){
    if(!pathExist(secondV)){return;} //проверяем есть ли ребро у вершины
    for(int i = 0; i < edgeList.size(); i++) { //проходимся по ребрам
        if(edgeList[i] -> secondVertex() -> getIndex() == secondV){ //если ребро ведет к вершине
            edgeList.erase(edgeList.begin() + i); //удаляем
        }
    }
    degree --; //количество ребер уменьшаем
}

//удалить все ребра
void Vertex::clearEdge(){
    edgeList.clear();
    degree = 0;
}

//меняем цвет
/*void Vertex::changeEdgeColor(int secondV){
    for(Edge *edge : edgeList){
        if(edge->secondVertex()->getIndex() == secondV){
            edge->setColor("black");
        }
    }
}*/

QPointF Vertex::getPos(){return newPos;} //возвращаем текущую позицию вершины

//определяем границы сцены при отрисовке вершин
QRectF Vertex::boundingRect() const{
    qreal adjust = 2;
    return QRectF(-20 - adjust, -20 - adjust, 40 + adjust, 40 + adjust);
}

QPainterPath Vertex::shape() const{
    QPainterPath path;
    path.addEllipse(-20, -20, 40, 40);
    return path;
}

void Vertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *){

    painter->setPen(QColor::fromRgb(0,0,0));
    painter->setBrush(QColor::fromRgb(220, 20, 60));

    QRadialGradient gradient(-5, -5, 20);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        //gradient.setColorAt(1, QColor(QColor::fromRgb(152, 251, 152)).lighter(120));
        gradient.setColorAt(0, QColor(QColor::fromRgb(205, 92, 92)).lighter(120));
        /*else if (this -> color == "gray"){
            gradient.setColorAt(1, QColor(Qt::lightGray).lighter(120));
            gradient.setColorAt(0, QColor(Qt::darkGray).lighter(120));
        }
        else if (this -> color == "black"){
            gradient.setColorAt(1, QColor(QColor::fromRgb(106, 90, 205)).lighter(120));
            gradient.setColorAt(0, QColor(QColor::fromRgb(205, 92, 92)).lighter(120));
        }*/

    } else {
        if (this -> color == "white"){
            gradient.setColorAt(0, QColor(QColor::fromRgb(205, 92, 92)).lighter(120));
            gradient.setColorAt(1, QColor(QColor::fromRgb(220, 20, 60)).lighter(120));
        }
        else if (this -> color == "gray"){
            gradient.setColorAt(0, QColor(Qt::lightGray).lighter(120));
            gradient.setColorAt(1, QColor(Qt::darkGray).lighter(120));
        }
        else if (this -> color == "black"){
            gradient.setColorAt(0, QColor(QColor::fromRgb(106, 90, 205)).lighter(120));
            gradient.setColorAt(1, QColor(QColor::fromRgb(72, 61, 139)).lighter(120));
        }
    }
    painter->setBrush(gradient);
    painter->setPen(QPen(Qt::black, 2));
    painter->drawEllipse(-20, -20, 40, 40);
    QString index = QString::number(vertexIndex);
    QFont font = painter->font();
    font.setPointSize(14); // Установка размера шрифта
    painter->setFont(font);
    painter->drawText(QRect(-20, -20, 40, 40), Qt::AlignCenter, index);
}

//обновляем вершину после того как мы ее поменяли
QVariant Vertex::itemChange(GraphicsItemChange change, const QVariant &value){
    switch(change){
    case ItemPositionHasChanged:
        //если поменяли позицию.
        for(Edge *edge : qAsConst(edgeList)){ //перебираем все ребра
            graph->itemMoved(); //обновляем граф, мы в нем что-то подвинули
            edge->tuneEdge(); //ребра пересчитываем и обновляем их положение на вершинах
            for(Edge *reverseEdge : edge->secondVertex()->getEdges()){ //перебираем ребра обратно
                reverseEdge->tuneEdge(); //также регулируем их положение на вершинах
            }
        }
        graph->itemMoved(); //метод обработки изменений позиции элемента в конце обработки всех связанных ребер.
        break;
    default:
        break;
    };
    return QGraphicsItem::itemChange(change, value);
}

//обработка щелчков мыши
void Vertex::mousePressEvent(QGraphicsSceneMouseEvent *event){
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Vertex::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
