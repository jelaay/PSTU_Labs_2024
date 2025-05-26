#include "vertex.h"
#include "edge.h"
#include "graph.h"

#include <QtMath>


#define M_PI 3.1415926

//инициализируем ребро. все входные данные в edge.h
Edge::Edge(Vertex *firstV, Vertex *secondV, double weight){
    this->firstV = firstV; //устанавливаем указатель в начальную вершину и передаем ей значение
    this->secondV = secondV; //то же самое для второй (конечной) вершины
    //setAcceptedMouseButtons(Qt::NoButton); //
    firstV->addEdge(this); //добавляем текущее ребро в список ребер у вершины
    this->weight = weight; //устанавливаем указатель на вес и передаем параметр
    color = "white"; //устаналиваем цвет
    tuneEdge();
}

Edge::~Edge(){}

Vertex *Edge::firstVertex() const{ //возвращаем вершину А
    return firstV;
}

Vertex *Edge::secondVertex() const{ //возвращаем вершину Б
    return secondV;
}

//регулируем положение ребра между вершинами
void Edge::tuneEdge(){
    if(!firstV || !secondV){return;} //проверяем, что вершины существуют
    //линия между вершиной А и вершиной Б
    QLineF line(mapFromItem(firstV, 0, 0), mapFromItem(secondV, 0, 0));
    qreal length = line.length(); //вычисляем длину линии
    prepareGeometryChange(); //обновляем отображение ребра

    //вычисляем положение ребра
    if(length > qreal(20)){ //если длина ребра больше 20
        QPointF edgeOffset((line.dx() * 20) / length, (line.dy() * 20) / length); //смотрим смещение ребра
        firstVPoint = line.p1() + edgeOffset; //устанавливаем точку на вершине А, откуда пойдет ребро
        secondVPoint = line.p2() - edgeOffset; //устанавливаем току на вершине Б, куда пойдет ребро
    } else {
        firstVPoint = secondVPoint = line.p1(); //если точки на одной позиции, то рисуем прямую линию
    }
}


QRectF Edge::boundingRect() const{
    if(!firstV || !secondV){return QRectF();} //проверяем существование вершин
    qreal penWidth = 5; //толщина линии
    qreal extra = (penWidth + arrowSize) / 2;//дополнительное место для стрелки
    //возвращаем прямоугольник с началом firstVPoint и размером (разница между вершиной А и вершиной Б)
    //делаем ширину и высоту положительными
    //регулируем размер прямоугольника в зависимости от толщины линии, размера стрелки
    return QRectF(firstVPoint, QSizeF(secondVPoint.x() - firstVPoint.x(), secondVPoint.y() - firstVPoint.y())).normalized().adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    if(!firstV || !secondV){return;} //проверяем существование вершин
    QLineF line(firstVPoint, secondVPoint); //рисуем линию между точками, которые мы высчитывали для корректного отображения ребра
    if(qFuzzyCompare(line.length(), qreal(0.))){return;} //если линия равна 0, то точки совпали

    //вычисление координат для отображения стрелки
    double angle = atan2(-line.dy(), line.dx());
    QPointF destArrowP1 = secondVPoint + QPointF(sin(angle - M_PI / 3) * arrowSize, cos(angle - M_PI / 3) * arrowSize);
    QPointF destArrowP2 = secondVPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize, cos(angle - M_PI + M_PI / 3) * arrowSize);


    if(color == "white"){
        painter->setBrush(Qt::black);
        painter->setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
    else if(color == "black"){
        painter->setBrush(Qt::red);
        painter->setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
    QFont font = painter->font();  // Получаем текущий шрифт
    font.setPointSize(14);  // Устанавливаем размер шрифта 14
    painter->setFont(font);
    painter->drawLine(line); //финально рисуем ребро
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2); //рисуем стрелку
    //пишем над ребром вес

    painter->drawText(QRectF(QPointF(firstVPoint.x() - 20, firstVPoint.y() - 20), QPointF(secondVPoint.x() + 20, secondVPoint.y() + 20)), Qt::AlignCenter, QString::number(weight));
}

double Edge::getWeight(){
    return weight; //получаем вес
}

void Edge::setWeight(double w){
    weight = w; //устанавливаем новый вес для ребра
}

QString Edge::getColor(){
    return color; //получаем вес
}

void Edge::setColor(QString color){
    this -> color = color; //принимаем новый цвет
    qApp->processEvents(); //выполняем событие
    update(); //обновляем
}
