#include "graph.h"
#include <QTextStream>
#include <QMessageBox>
#include "priority_queue.h"
#include <QThread>
#include <QMessageBox>
#include <algorithm>
#include <limits>
#include <queue>

struct Kommivoyajer {
    QVector<int> path; // Текущий маршрут
    int cost;  // Стоимость текущего маршрута
    int vertex; // Последняя посещенная вершина
    QVector<bool> visited; // Посещенные вершины
};

Graph::Graph(QWidget *parent) : QGraphicsView(parent){
    scene = new QGraphicsScene(this); //устанавливаем сцену
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-500, -550, 1000, 1000); //размер сцены и точка О(0,0)
    setScene(scene);
    setCacheMode(CacheBackground); //улучшаем отрисовку
    setViewportUpdateMode(BoundingRectViewportUpdate); //обновляем область видимости
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(1000, 1000);

    connected = true;
    DFS.clear(); //очистка обхода в глубину
    BFS.clear(); //очистка обхода в ширину
}

void Graph::itemMoved(){
    if(!timerId){timerId = startTimer(1000 / 25);} //если таймер неактивен, то начинаем таймер
    //это нужно для отрисовки каждого кадра
}

void Graph::timerEvent(QTimerEvent *event){
    const QList<QGraphicsItem *> items = scene -> items(); //получаем количество элементов на сцене
    for(Vertex *temp : qAsConst(vertexList)){// Проходим по списку вершин (vertexList)
        temp->calculateForces();// Вызываем метод calculateForces() для каждой вершины
    }
    bool itemsMoved = false;// Инициализируем флаг, указывающий перемещались ли элементы
    for(Vertex *temp : qAsConst(vertexList)){// Снова проходим по списку вершин
        if(temp->advancePosition()){// Если вершина переместилась и метод возвращает true
            itemsMoved = true;// Устанавливаем флаг перемещения элементов в true
        }
    }

    if(!itemsMoved){// Если ни один элемент не перемещался
        killTimer(timerId);// Останавливаем таймер
        timerId = 0;// Сбрасываем идентификатор таймера
    }
}
//рисуем фон и рисуем менюшку
void Graph::drawBackground(QPainter *painter, const QRectF &rect){

    QRectF sceneRect = this->sceneRect();
    QLinearGradient colorBack(sceneRect.topLeft(), sceneRect.bottomRight());
    colorBack.setColorAt(0, QColor::fromRgb(245, 255, 250));
    painter->fillRect(rect.intersected(sceneRect), colorBack);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + sceneRect.height()/9 + 35, sceneRect.width() - 4, 20);
    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(50);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    createTabWidget(rect);
}

//создаем менюшку
void Graph::createTabWidget(const QRectF &rect){
    QRectF sceneRect = this->sceneRect();  // Получаем прямоугольник сцены
    QTabWidget *tab = new QTabWidget();// Создаем новый виджет вкладок (QTabWidget)

    // Устанавливаем геометрию виджета вкладок - располагаем его в верхней части сцены с высотой sceneRect.height()/9
    tab->setGeometry(sceneRect.left() + 1, sceneRect.top(), sceneRect.width() - 1, sceneRect.height()/9);

    // Создаем три виджета для каждой вкладки
    QWidget *vertexTab = new QWidget;
    QWidget *edgeTab = new QWidget;
    QWidget *graphTab = new QWidget;

    // Создаем объект шрифта и устанавливаем размер шрифта 12
    QFont textfont = QFont();
    textfont.setPointSize(12);
    tab->setFont(textfont);

    // Добавляем три вкладки в виджет вкладок: "Вершина", "Ребро" и "О графе"
    tab->addTab(vertexTab,  tr("Вершина"));
    tab->addTab(edgeTab, tr("Ребро"));
    tab->addTab(graphTab, tr("О графе"));

    // Создаем горизонтальный layout для вкладки "Вершина"
    QHBoxLayout *vertexTabLayout = new QHBoxLayout;

    // Создаем кнопку для добавления вершины
    QPushButton *addVertexButton = new QPushButton();
    addVertexButton->setText(tr("Добавить вершину")); // Устанавливаем текст кнопки
    addVertexButton->setFont(textfont); // Устанавливаем шрифт кнопки
    addVertexButton->setMaximumSize(QSize(201, 35)); // Устанавливаем максимальный размер кнопки
    // Подключаем сигнал нажатия кнопки к слоту добавления вершины
    connect(addVertexButton, &QPushButton::clicked, this, &Graph::insertVertex);

    // Создаем кнопку для удаления вершины
    QPushButton *eraseVertexButton = new QPushButton();
    eraseVertexButton->setText(tr("Удалить вершину")); // Устанавливаем текст кнопки
    eraseVertexButton->setFont(textfont); // Устанавливаем шрифт кнопки
    eraseVertexButton->setMaximumSize(QSize(201, 35)); // Устанавливаем максимальный размер кнопки
    // Подключаем сигнал нажатия кнопки к слоту создания окна для удаления вершины
    connect(eraseVertexButton, &QPushButton::clicked, this, &Graph::createEraseVertexWindow);

    // Добавляем кнопки в горизонтальный layout для вкладки "Вершина"
    vertexTabLayout->addWidget(addVertexButton);
    vertexTabLayout->addWidget(eraseVertexButton);

    // Устанавливаем layout для вкладки "Вершина"
    vertexTab->setLayout(vertexTabLayout);

    QPushButton *setVertexPosButton = new QPushButton();
    setVertexPosButton->setText(tr("Изменить вершину"));
    setVertexPosButton->setFont(textfont);
    setVertexPosButton->setMaximumSize(QSize(201, 35));
    connect(setVertexPosButton, &QPushButton::clicked, this, &Graph::createSetVertexPosWindow);


    vertexTabLayout->addWidget(addVertexButton);
    vertexTabLayout->addWidget(eraseVertexButton);
    vertexTabLayout->addWidget(setVertexPosButton);

    QHBoxLayout *edgeTabLayout = new QHBoxLayout;
    QPushButton *addEdgeButton = new QPushButton();
    addEdgeButton->setText(tr("Соединить вершины"));
    addEdgeButton->setFont(textfont);
    addEdgeButton->setMaximumSize(QSize(201, 35));
    connect(addEdgeButton, &QPushButton::clicked, this, &Graph::createAddEdgeWindow);

    QPushButton *updateWeightButton = new QPushButton();
    updateWeightButton->setText(tr("Изменить вес"));
    updateWeightButton->setFont(textfont);
    updateWeightButton->setMaximumSize(QSize(201, 35));
    connect(updateWeightButton, &QPushButton::clicked, this, &Graph::createUpdateWeightWindow);



    QPushButton *eraseEdgeButton = new QPushButton();
    eraseEdgeButton->setText(tr("Удалить ребро"));
    eraseEdgeButton->setFont(textfont);
    eraseEdgeButton->setMaximumSize(QSize(201, 35));
    connect(eraseEdgeButton, &QPushButton::clicked, this, &Graph::createEraseEdgeWindow);

    edgeTabLayout->addWidget(addEdgeButton);
    edgeTabLayout->addWidget(updateWeightButton);
    edgeTabLayout->addWidget(eraseEdgeButton);

    QHBoxLayout *graphTabLayout = new QHBoxLayout;

    QToolButton *functionButton = new QToolButton();
    functionButton->setText(tr("Выполнить"));
    functionButton->setFont(textfont);
    functionButton->setMaximumSize(QSize(150, 35));


    QMenu *menu = new QMenu;
    menu->setFixedWidth(220);

    QAction *dfs = new QAction(tr("Обход в глубину"), this);
    dfs->setStatusTip(tr("Обход в глубину"));
    connect(dfs, &QAction::triggered, this, &Graph::createDFSWindow);
    menu->addAction(dfs);
    menu->addSeparator();

    QAction *bfs = new QAction(tr("Обход в ширину"), this);
    bfs->setStatusTip(tr("Обход в ширину"));
    connect(bfs, &QAction::triggered, this, &Graph::createBFSWindow);
    menu->addAction(bfs);
    menu->addSeparator();

    QAction *dijkstra = new QAction(tr("Алгоритм Дейкстры"), this);
    dijkstra->setStatusTip(tr("Алгоритм Дейкстры"));
    connect(dijkstra, &QAction::triggered, this, &Graph::createDijkstraWindow);
    menu->addAction(dijkstra);
    menu->addSeparator();

    QAction *TSP = new QAction(tr("Задача Коммивояжера"), this);
    TSP->setStatusTip(tr("Задача Коммивояжера"));
    connect(TSP, &QAction::triggered, this, &Graph::createTSPWindow);
    menu->addAction(TSP);
    menu->addSeparator();

    functionButton->setPopupMode(QToolButton::InstantPopup);
    functionButton->setMenu(menu);

    QPushButton *resetButton = new QPushButton();
    resetButton->setText(tr("Сбросить"));
    resetButton->setFont(textfont);
    resetButton->setMaximumSize(QSize(150, 35));
    connect(resetButton, &QPushButton::clicked, this, &Graph::reset);

    QPushButton *clearButton = new QPushButton();
    clearButton->setText(tr("Удалить все"));
    clearButton->setFont(textfont);
    clearButton->setMaximumSize(QSize(201, 35));
    connect(clearButton, &QPushButton::clicked, this, &Graph::clear);

    QPushButton *graphInfoButton = new QPushButton();
    graphInfoButton->setText(tr("Матрица смежности"));
    graphInfoButton->setFont(textfont);
    graphInfoButton->setMaximumSize(QSize(201, 35));
    connect(graphInfoButton, &QPushButton::clicked, this, &Graph::getGraphInfo);

    graphTabLayout->addWidget(functionButton);
    graphTabLayout->addWidget(resetButton);
    graphTabLayout->addWidget(clearButton);
    graphTabLayout->addWidget(graphInfoButton);

    vertexTab->setLayout(vertexTabLayout);
    edgeTab->setLayout(edgeTabLayout);
    graphTab->setLayout(graphTabLayout);

    scene->addWidget(tab);
}

int Graph::getVertexNum(){
    return vertexList.size(); // Возвращает количество вершин в графе
}

void Graph::scaleView(qreal scaleFactor){
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width(); // Вычисляет новый масштаб просмотра

    if(factor < 0.07 || factor > 100){ // Проверка на допустимые пределы масштаба
        return; // Предотвращает слишком маленький или слишком большой масштаб
    }

    scale(scaleFactor, scaleFactor); // Масштабирование сцены
}

void Graph::insertVertex(){
    int vertexIndex = vertexList.size(); // Получаем индекс новой вершины
    vertexList.append(new Vertex(this, vertexIndex)); // Добавляем новую вершину в список
    vertexList[vertexIndex]->setPos(0, 50); // Устанавливаем позицию новой вершины
    scene->addItem(vertexList[vertexIndex]); // Добавляем вершину на сцену
    vertexNum++; // Увеличиваем счетчик вершин
}

void Graph::updateIndex(){
    for(int i = 0; i < vertexList.size(); i++){ // Перебираем все вершины
        vertexList[i]->setIndex(i); // Обновляем индекс каждой вершины
    }
}

void Graph::setVertexPos(int vertexIndex, double x, double y){
    Vertex *temp = vertexList[vertexIndex]; // Получаем временную переменную для вершины с указанным индексом
    temp->setPos(QPointF(x, y)); // Устанавливаем новые координаты для вершины
}

void Graph::eraseVertex(int vertexIndex){
    Vertex *temp = vertexList[vertexIndex]; // Получаем указатель на вершину, которую нужно удалить

    for(Edge *edge : temp->getEdges()){ // Перебираем все ребра, связанные с вершиной
        eraseEdge(vertexIndex, edge->secondVertex()->getIndex()); // Удаляем ребра между текущей вершиной и другими
    }

    temp->clearEdge(); // Удаляем все ребра, связанные с текущей вершиной
    scene->removeItem(temp); // Удаляем вершину со сцены
    edgeNum -= vertexList[vertexIndex]->getEdges().size() * 2; // Уменьшаем количество ребер
    vertexList.erase(vertexList.begin() + vertexIndex); // Удаляем вершину из списка вершин
    updateIndex(); // Обновляем индексы оставшихся вершин
    vertexNum--; // Уменьшаем количество вершин
}

void Graph::getVertexInfo(int vertexIndex){
    QTableWidget *infoWindow = new QTableWidget; // Создание нового виджета таблицы
    Vertex *temp = vertexList[vertexIndex]; // Получение вершины по индексу

    int vertexDegree = temp->getDegree(); // Получение степени вершины

    infoWindow->setRowCount(vertexDegree + 5); // Установка количества строк в таблице
    infoWindow->setColumnCount(2); // Установка количества столбцов в таблице

    infoWindow->setItem(0, 0, new QTableWidgetItem("Свойства")); // Установка названия первой строки
    infoWindow->setItem(0, 1, new QTableWidgetItem("Размер")); // Установка заголовка столбца

    infoWindow->setItem(1, 0, new QTableWidgetItem("Вершина")); // Информация о вершине: метка
    infoWindow->setItem(1, 1, new QTableWidgetItem(QString::number(vertexIndex))); // Информация о вершине: индекс

    infoWindow->setItem(2, 0, new QTableWidgetItem("Координаты")); // Информация о координатах вершины
    QString x = QString::number(temp->getPos().x());
    QString y = QString::number(temp->getPos().y());
    QString coordinate = "X: " + x + " ; Y: " + y; // Формирование строки с координатами
    infoWindow->setItem(2, 1, new QTableWidgetItem(coordinate)); // Информация о координатах: значение

    infoWindow->setItem(3, 0, new QTableWidgetItem("Посещение")); // Информация о посещении вершины
    bool visited = (vertexList[vertexIndex]->getColor() == "black"); // Проверка посещения вершины
    infoWindow->setItem(3, 1, new QTableWidgetItem(QString::number(visited))); // Значение о посещении вершины

    infoWindow->setItem(4, 0, new QTableWidgetItem("Номер вершины")); // Информация о номере вершины
    infoWindow->setItem(4, 1, new QTableWidgetItem(QString::number(vertexDegree))); // Значение о номере вершины

    infoWindow->setItem(5, 0, new QTableWidgetItem("Соседние вершины")); // Информация о соседних вершинах
    int rowCounter = 5; // Счетчик строк для соседних вершин

    for(Edge *edge : vertexList[vertexIndex]->getEdges()){ // Перебор ребер, инцидентных данной вершине
        QString adjacentVertex = QString::number(vertexIndex) + " -> " + QString::number(edge->secondVertex()->getIndex()) + " ; weight: " + QString::number(edge->getWeight());
        infoWindow->setItem(rowCounter, 1, new QTableWidgetItem(adjacentVertex)); // Добавление информации о соседних вершинах
        rowCounter++; // Увеличение счетчика строк

    }

    infoWindow->setWindowTitle(tr("Матрица смежности")); // Заголовок окна
    infoWindow->setColumnWidth(0, 140); // Установка ширины столбца 0
    infoWindow->setColumnWidth(1, 220); // Установка ширины столбца 1
    infoWindow->setFixedSize(QSize(380, 400)); // Установка фиксированного размера окна
    infoWindow->show(); // Отображение окна
}

void Graph::getGraphInfo(){
    // Создание таблицы для отображения информации о графе
    int rows = vertexList.size() + 5;
    int cols = vertexList.size()+1;
    QTableWidget *infoWindow = new QTableWidget(rows, cols);

    // Алгоритм Дейкстры
    QString dijkstra1 = "Алгоритм Дейкстры по индексу ";
    if(dijkstraSignal() != -1){ // Если есть сигнал для алгоритма Дейкстры
        QVector<int> k = dijkstra(dijkstraSignal()); // Вызов функции Дейкстры
        dijkstra1 += QString::number(dijkstraSignal()); // Добавление информации о вершине
        // Заполнение ячеек таблицы результатами алгоритма Дейкстры
        for(int i = 0; i < k.size(); i++){
            infoWindow->setItem(0, i + 1, new QTableWidgetItem(QString::number(k[i])));
        }
    }
    infoWindow->setItem(0, 0, new QTableWidgetItem(dijkstra1)); // Установка информации в таблицу

    // Обход в глубину
    QString dfs = "Обход в глубину по индексу ";
    if(!DFS.empty()){ // Если массив DFS не пуст
        dfs += QString::number(DFS[0]); // Добавление первой вершины к информации о глубинном обходе
        // Заполнение ячеек таблицы информацией о глубинном обходе
        for(int i = 0; i < DFS.size(); i++){
            infoWindow->setItem(1, i + 1, new QTableWidgetItem(QString::number(DFS[i])));
        }
    }
    infoWindow->setItem(1, 0, new QTableWidgetItem(dfs)); // Установка информации о глубинном обходе в таблицу

    // Обход в ширину
    QString bfs = "Обход в ширину по индексу ";
    if(!BFS.empty()){ // Если массив BFS не пуст
        bfs += QString::number(BFS[0]); // Добавление первой вершины к информации о обходе в ширину
        // Заполнение ячеек таблицы информацией о обходе в ширину
        for(int i = 0; i < BFS.size(); i++){
            infoWindow->setItem(2, i + 1, new QTableWidgetItem(QString::number(BFS[i])));
        }
    }
    infoWindow->setItem(2, 0, new QTableWidgetItem(bfs)); // Установка информации о задаче в таблицу


    // Задача Коммивояжера
    QString komi = "Задача Коммивояжера по индексу ";
    if(TSPSignal() != -1){ // Если есть сигнал для алгоритма
        QVector<int> t = TSP(TSPSignal()); // Вызов функции
        komi += QString::number(TSPSignal()); // Добавление информации о вершине
        // Заполнение ячеек таблицы результатами
        for(int i = 0; i < t.size(); i++){
            infoWindow->setItem(3, i + 1, new QTableWidgetItem(QString::number(t[i])));
        }
    }
    infoWindow->setItem(3, 0, new QTableWidgetItem(komi)); // Установка информации в таблицу



    // Матрица
    infoWindow->setItem(4, 0, new QTableWidgetItem("Матрица")); // Установка заголовка для матрицы
    infoWindow->item(4, 0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter); // Выравнивание заголовка

    // Отобразить вершины
    for(int i = 0; i < vertexNum; i++){
        infoWindow->setItem(4, i + 1, new QTableWidgetItem(QString::number(i))); // Отображение вершин в таблице
        infoWindow->item(4, i + 1)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter); // Выравнивание вершин
    }

    // Заполнение матрицы смежности
    for(int i = 0; i < vertexNum; i++){
        infoWindow->setItem(5 + i, 0, new QTableWidgetItem(QString::number(i))); // Отображение номеров вершин
        infoWindow->item(5 + i, 0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter); // Выравнивание номеров вершин
        for(int j = 0; j < vertexNum; j++){
            infoWindow->setItem(5 + i, 1 + j, new QTableWidgetItem("0")); // Инициализация матрицы нулями
            infoWindow->item(5 + i, 1 + j)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter); // Выравнивание элементов
        }
        // Заполнение матрицы смежности значениями ребер и их весами
        for(Edge *edge : vertexList[i]->getEdges()){
            int pos = edge->secondVertex()->getIndex();
            infoWindow->setItem(5 + i, 1 + pos, new QTableWidgetItem(QString::number(edge->getWeight()))); // Добавление весов ребер
            infoWindow->item(5 + i, 1 + pos)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter); // Выравнивание весов
        }
        infoWindow->setColumnWidth(i + 1, 30); // Установка ширины столбца
    }

    // Настройка окна таблицы
    infoWindow->setWindowTitle("Информация о графе"); // Установка заголовка окна
    infoWindow->setColumnWidth(0, 275); // Установка ширины нулевого столбца
    infoWindow->setFixedSize(QSize(600, 700)); // Установка фиксированного размера окна
    infoWindow->show(); // Показать окно
}
void Graph::insertEdge(int source, int dest, double weight){
    if(checkAdjacent(source, dest)){ // Проверяем, являются ли вершины source и dest смежными
        return; // Если вершины уже смежные, то выходим из функции
    } else {
        scene->addItem(new Edge(vertexList[source], vertexList[dest], weight)); // Добавляем ребро от вершины source к вершине dest на сцену
        scene->addItem(new Edge(vertexList[dest], vertexList[source], weight)); // Добавляем ребро от вершины dest к вершине source на сцену
        edgeNum += 2; // Увеличиваем счетчик количества ребер на 2
    }
}

void Graph::updateWeight(int source, int dest, double weight){
    if(!checkAdjacent(source, dest)){ // Проверяем, являются ли вершины source и dest смежными
        return; // Если вершины не смежные, то выходим из функции
    }
    vertexList[source]->updateWeight(dest, weight); // Обновляем вес ребра между вершинами source и dest в вершине source
    vertexList[dest]->updateWeight(source, weight); // Обновляем вес ребра между вершинами dest и source в вершине dest
}

void Graph::eraseEdge(int source, int dest){
    if(!checkAdjacent(source, dest)){ // Проверяем, являются ли вершины source и dest смежными
        scene->addText(tr("Вершины не соединены")); // Выводим сообщение, что вершины не соединены
        return; // Если вершины не смежные, то выходим из функции
    }
    for(Edge *edge : vertexList[source]->getEdges()){ // Перебираем все ребра вершины source
        if(edge->secondVertex()->getIndex() == dest){ // Если ребро соединяет вершину source и dest
            vertexList[source]->eraseEdge(dest); // Удаляем ребро из вершины source
            scene->removeItem(edge); // Удаляем ребро со сцены
        }
    }
    for(Edge *edge : vertexList[dest]->getEdges()){ // Перебираем все ребра вершины dest
        if(edge->secondVertex()->getIndex() == source){ // Если ребро соединяет вершину dest и source
            vertexList[dest]->eraseEdge(source); // Удаляем ребро из вершины dest
            scene->removeItem(edge); // Удаляем ребро со сцены
        }
    }
    edgeNum -= 2; // Уменьшаем счетчик количества ребер на 2
}

bool Graph::checkAdjacent(int source, int dest){
    return vertexList[source]->pathExist(dest); // Проверяет существует ли путь от вершины source к вершине dest
}

int Graph::getDegree(int vertexIndex){
    return vertexList[vertexIndex]->getDegree(); // Возвращает степень вершины с указанным индексом
}
void Graph::clear(){
    while(!vertexList.empty()){ // Пока список вершин не пуст
        eraseVertex(0); // Удаляет вершину с индексом 0 (происходит поочередное удаление всех вершин)
    }
}

void Graph::checkConnected(){
    connected = true; // Устанавливаем флаг "connected" в истину
    for(Vertex *vertex : vertexList){ // Для каждой вершины в графе
        bool visited = false; // Инициализируем флаг посещения вершины
        if(vertex->getColor() == "black"){ // Если вершина посещена
            visited = true; // Устанавливаем флаг посещения в истину
        }
        connected &= visited; // Устанавливаем флаг "connected" в истину, если все вершины посещены
    }
}

void Graph::reset(){
    if(vertexList.size() == 0){ // Если список вершин пуст
        return; // Возвращаемся из функции
    }
    for(int i = 0; i < vertexList.size(); i++){ // Для каждой вершины в графе
        vertexList[i]->setColor("white"); // Сбрасываем цвет вершины на белый
        for(Edge *edge : vertexList[i]->getEdges()){ // Для каждого ребра выходящего из текущей вершины
            edge->setColor("white"); // Сбрасываем цвет ребра на белый
        }
    }
}

void Graph::dfsUtil(int vertexIndex, QVector<bool> &visited){
    QStack<int> dfsStack; // Создаем стек для выполнения обхода в глубину
    dfsStack.push(vertexIndex); // Добавляем начальную вершину в стек

    while(!dfsStack.empty()){ // Пока стек не пуст
        int temp = dfsStack.top(); // Получаем вершину с вершины стека
        Vertex *tempVertex = vertexList[temp]; // Получаем указатель на вершину по индексу temp
        dfsStack.pop(); // Удаляем вершину из стека
        if(!visited[temp]){ // Если вершина не посещена
            visited[temp] = true; // Устанавливаем флаг посещения
            vertexList[temp]->setColor("black"); // Устанавливаем цвет вершины как посещенную
            DFS.push_back(temp); // Добавляем вершину в список обхода в глубину
            delay(300); // Задержка для визуализации
        }
        for(Edge *tempEdge : tempVertex->getEdges()){ // Для каждого ребра, инцидентного текущей вершине
            if(!visited[tempEdge->secondVertex()->getIndex()]){ // Если конечная вершина ребра не посещена
                tempEdge->secondVertex()->setColor("black"); // Устанавливаем цвет следующей вершины как "серый"
                delay(300); // Задержка для визуализации
                dfsStack.push(tempEdge->secondVertex()->getIndex()); // Добавляем индекс следующей вершины в стек
            }
        }
    }
}

void Graph::dfs(int vertexIndex){
    DFS.clear(); // Очищаем список обхода в глубину
    QVector<bool> visited(vertexList.size(), false); // Создаем вектор для отслеживания посещенных вершин, все инициализируются как не посещенные
    dfsUtil(vertexIndex, visited); // Вызываем вспомогательную функцию для выполнения обхода в глубину из заданной вершины
    checkConnected(); // Проверяем, связан ли граф после выполнения обхода в глубину
}

void Graph::bfsUtil(int vertexIndex, QVector<bool> &visited){
    QQueue<int> bfsQueue; // Создаем очередь для выполнения обхода в ширину
    bfsQueue.push_back(vertexIndex); // Добавляем начальную вершину в очередь

    while(!bfsQueue.empty()){ // Пока очередь не пуста
        int temp = bfsQueue.front(); // Получаем вершину из начала очереди
        Vertex *tempVertex = vertexList[temp]; // Получаем указатель на вершину по индексу temp
        bfsQueue.pop_front(); // Удаляем вершину из очереди

        if(!visited[temp]){ // Если вершина не посещена
            visited[temp] = true; // Устанавливаем флаг посещения
            tempVertex->setColor("black"); // Устанавливаем цвет вершины как посещенную
            BFS.push_back(temp); // Добавляем вершину в список обхода в ширину
            delay(300); // Задержка для визуализации
        }

        for(Edge *tempEdge : tempVertex->getEdges()){ // Для каждого ребра, инцидентного текущей вершине
            if(!visited[tempEdge->secondVertex()->getIndex()]){ // Если конечная вершина ребра не посещена
                tempEdge->secondVertex()->setColor("black"); // Устанавливаем цвет следующей вершины как посещенной
                bfsQueue.push_back(tempEdge->secondVertex()->getIndex()); // Добавляем индекс следующей вершины в очередь
                delay(300); // Задержка для визуализации
            }
        }
    }
}

void Graph::bfs(int vertexIndex){
    BFS.clear(); // Очищаем список обхода в ширину
    QVector<bool> visited(vertexList.size(), false); // Создаем вектор для отслеживания посещенных вершин, все инициализируются как не посещенные
    bfsUtil(vertexIndex, visited); // Вызываем вспомогательную функцию для выполнения обхода в ширину из заданной вершины
    checkConnected(); // Проверяем, связан ли граф после выполнения обхода в ширину
}




int calculateLowerBound(const Kommivoyajer& node, const QVector<QVector<int>>& adjMatrix) {
    int lowerBound = node.cost;
    int n = adjMatrix.size();

    // Находим минимальное ребро из непосещенных вершин
    for (int i = 0; i < n; ++i) {
        if (!node.visited[i]) {
            int minEdge = std::numeric_limits<int>::max();
            for (int j = 0; j < n; ++j) {
                if (i != j && adjMatrix[i][j] < minEdge) {
                    minEdge = adjMatrix[i][j];
                }
            }
            lowerBound += minEdge;
        }
    }

    return lowerBound;
}

QVector<int> Graph::TSP(int startVertexIndex) {
    int n = vertexNum;
    QVector<QVector<int>> adjMatrix(n, QVector<int>(n));

    // Заполняем матрицу смежности из вашего списка ребер
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < vertexList[i]->getEdges().count(); ++j) {
            Edge* e = vertexList[i]->getEdges()[j];
            adjMatrix[i][e->secondVertex()->getIndex()] = e->getWeight();
            adjMatrix[e->secondVertex()->getIndex()][i] = e->getWeight(); // Добавляем симметричное ребро
        }
    }

    QVector<int> bestPath;
    int bestCost = std::numeric_limits<int>::max();

    // Создаем начальный узел
    Kommivoyajer startcity;
    startcity.path = {startVertexIndex};
    startcity.cost = 0;
    startcity.vertex = startVertexIndex;
    startcity.visited = QVector<bool>(n, false);
    startcity.visited[startVertexIndex] = true;

    // Создаем очередь с приоритетом (min-heap) для узлов
    std::priority_queue<Kommivoyajer, std::vector<Kommivoyajer>, std::function<bool(const Kommivoyajer&, const Kommivoyajer&)>> pq([](const Kommivoyajer& a, const Kommivoyajer& b) { return a.cost > b.cost; }); // Сортировка по возрастанию стоимости
    pq.push(startcity);

    while (!pq.empty()) {
        Kommivoyajer current = pq.top();
        pq.pop();

        // Если посетили все вершины, проверяем, лучше ли этот путь
        if (current.path.size() == n) {
            int finalCost = current.cost + adjMatrix[current.vertex][startVertexIndex];
            if (finalCost < bestCost) {
                bestCost = finalCost;
                bestPath = current.path;
                bestPath.push_back(startVertexIndex); // Добавляем начальную вершину в конец
            }
            continue;
        }

        // Расширяем текущий узел, добавляя непосещенных соседей
        for (int i = 0; i < n; ++i) {
            if (!current.visited[i] && adjMatrix[current.vertex][i] != 0) {
                Kommivoyajer next = current;
                next.path.push_back(i);
                next.cost += adjMatrix[current.vertex][i];
                next.vertex = i;
                next.visited[i] = true;

                // Рассчитываем нижнюю границу и добавляем узел в очередь, если он потенциально лучше
                int lowerBound = calculateLowerBound(next, adjMatrix);
                if (lowerBound < bestCost) {
                    pq.push(next);
                }
            }
        }
    }

    // Выводим общую длину маршрута
    QMessageBox::information(nullptr, "Маршрут",
        "Маршрут по задаче Коммивояжера (Ветви и Границы): " + QString::number(bestCost));

    return bestPath;
}


QVector<int> Graph::dijkstra(int vertexIndex){
    int Adj_matrix[vertexNum][vertexNum]; // Создаем матрицу смежности для алгоритма Дейкстры
    for(int i = 0; i < vertexNum; i++){
        for(int j = 0; j < vertexNum; j++){
            if(i == j) Adj_matrix[i][j] = 0; // Устанавливаем нули на диагонали
            else Adj_matrix[i][j] = 100000000; // Инициализируем все остальные ячейки с очень большим значением
        }
    }
    PriorityQueue<int> queue; // Создаем приоритетную очередь для хранения вершин
    for(int i = 0; i < vertexNum; i++){
        queue.enqueue(Adj_matrix[vertexIndex][i], i); // Добавляем начальные расстояния в очередь
    }
    while(queue.count() > 0){
        int Curr_vertex = queue.dequeue(); // Извлекаем вершину с наименьшим расстоянием
        int edge_count = vertexList[Curr_vertex]->getEdges().count(); // Получаем количество инцидентных ребер текущей вершины

        for(int i = 0; i < edge_count; i++){
            Edge* e = vertexList[Curr_vertex]->getEdges()[i]; // Получаем текущее ребро
            Vertex* dest = e->secondVertex(); // Получаем соседнюю вершину
            if(Adj_matrix[vertexIndex][Curr_vertex] + e->getWeight() < Adj_matrix[vertexIndex][dest->getIndex()]){
                int old = Adj_matrix[vertexIndex][dest->getIndex()]; // Старое расстояние до вершины
                Adj_matrix[vertexIndex][dest->getIndex()] = Adj_matrix[vertexIndex][Curr_vertex] + e->getWeight(); // Обновляем расстояние
                queue.update(old, dest->getIndex(), Adj_matrix[vertexIndex][dest->getIndex()]); // Обновляем вершину в очереди
            }
        }
    }
    QVector<int> new_vector; // Создаем вектор для хранения расстояний
    for(int i = 0; i < vertexNum; i++){
        new_vector.append(Adj_matrix[vertexIndex][i]); // Добавляем расстояния в вектор
    }
    return new_vector; // Возвращаем вектор с расстояниями
}

void Graph::delay(int time){
    clock_t now = clock();
    while(clock() - now < time);
}

void Graph::createEraseVertexWindow(){
    window = new QWidget; // Создание нового виджета
    input1 = new QLineEdit; // Создание поля ввода для индекса вершины, которую нужно удалить
    QLabel *label = new QLabel; // Создание метки (не используется)
    label->setFrameStyle(QFrame::Box | QFrame::Plain); // Установка стиля рамки для метки (не используется)
    QPushButton *okButton = new QPushButton(tr("Принять")); // Создание кнопки "Принять"

    QGridLayout *layout = new QGridLayout; // Создание сетки для компоновки виджетов
    layout->addWidget(new QLabel(tr("Вершина для удаления:")), 0, 0); // Добавление метки для поля ввода индекса вершины
    layout->addWidget(input1, 0, 1); // Добавление поля ввода для индекса вершины
    layout->addWidget(okButton, 1, 1, Qt::AlignRight); // Добавление кнопки "Принять" в сетку, выравнивание справа
    layout->setSizeConstraint(QLayout::SetFixedSize); // Установка фиксированного размера для сетки
    window->setLayout(layout); // Установка созданной сетки в качестве макета для виджета
    window->setWindowTitle("Удалить вершину"); // Установка заголовка окна

    connect(okButton, &QPushButton::clicked, this, &Graph::eraseVertexSignal); // Установка обработчика для сигнала нажатия кнопки
    window->show(); // Отображение окна
}

void Graph::eraseVertexSignal(){
    int srcIndex = input1->text().toInt(); // Получение индекса вершины для удаления из поля ввода
    window->close(); // Закрытие окна

    if(srcIndex >= vertexList.size()){ // Проверка условия: если индекс выходит за пределы списка вершин
        return; // Прерывание
    }
    eraseVertex(srcIndex); // Удаление вершины с указанным индексом
}

//изменить координаты
void Graph::createSetVertexPosWindow(){
    window = new QWidget; // Создание нового виджета
    input1 = new QLineEdit; // Создание поля ввода для индекса вершины
    input2 = new QLineEdit; // Создание поля ввода для новой координаты X
    input3 = new QLineEdit; // Создание поля ввода для новой координаты Y
    QLabel *label = new QLabel; // Создание метки (не используется)
    label->setFrameStyle(QFrame::Box | QFrame::Plain); // Установка стиля рамки для метки (не используется)
    QPushButton *okButton = new QPushButton(tr("Принять")); // Создание кнопки "Принять"

    QGridLayout *layout = new QGridLayout; // Создание сетки для компоновки виджетов
    layout->addWidget(new QLabel(tr("Вершина:")), 0, 0); // Добавление метки для ввода индекса вершины
    layout->addWidget(input1, 0, 1); // Добавление поля ввода для индекса вершины
    layout->addWidget(new QLabel(tr("Новая координата X:")), 1, 0); // Добавление метки для ввода новой координаты X
    layout->addWidget(input2, 1, 1); // Добавление поля ввода для новой координаты X
    layout->addWidget(new QLabel(tr("Новая координата Y:")), 2, 0); // Добавление метки для ввода новой координаты Y
    layout->addWidget(input3, 2, 1); // Добавление поля ввода для новой координаты Y
    layout->addWidget(okButton, 3, 1, Qt::AlignRight); // Добавление кнопки "Принять" в сетку, выравнивание справа
    layout->setSizeConstraint(QLayout::SetFixedSize); // Установка фиксированного размера для сетки
    window->setLayout(layout); // Установка созданной сетки в качестве макета для виджета
    window->setWindowTitle("Изменить координаты вершины"); // Установка заголовка окна

    connect(okButton, &QPushButton::clicked, this, &Graph::setVertexPosSignal); // Установка обработчика для сигнала нажатия кнопки
    window->show(); // Отображение окна
}

void Graph::setVertexPosSignal(){
    int vertexIndex = input1->text().toInt(); // Получение индекса вершины из поля ввода (преобразование в целое число)
    double xvel = input2->text().toDouble(); // Получение новой координаты X из поля ввода (преобразование в число с плавающей точкой)
    double yvel = input3->text().toDouble(); // Получение новой координаты Y из поля ввода (преобразование в число с плавающей точкой)
    window->close(); // Закрытие окна

    if(vertexIndex >= vertexList.size()){ // Проверка условия: если индекс выходит за пределы списка вершин
        return; // Прерывание
    }
    setVertexPos(vertexIndex, xvel, yvel); // Установка новых координат для указанной вершины
}

void Graph::createVertexInfoWindow(){
    window = new QWidget;
    input1 = new QLineEdit;
    QLabel *label = new QLabel;
    label -> setFrameStyle(QFrame::Box | QFrame::Plain);
    QPushButton *okButton = new QPushButton(tr("Принять"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(new QLabel(tr("Вершина")), 0, 0);
    layout->addWidget(input1, 0, 1);
    layout->addWidget(okButton, 1, 1, Qt::AlignRight);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    window->setLayout(layout);
    window->setWindowTitle("Информация о вершине");

    connect(okButton, &QPushButton::clicked, this, &Graph::vertexInfoSignal);
    window->show();
}

void Graph::vertexInfoSignal(){
    int index = input1->text().toInt();
    window->close();
    if(index >= vertexList.size()){
        return;
    }
    getVertexInfo(index);
}

void Graph::createAddEdgeWindow(){
    window = new QWidget; // Создание нового виджета
    input1 = new QLineEdit; // Создание поля ввода для начальной вершины
    input2 = new QLineEdit; // Создание поля ввода для конечной вершины
    input3 = new QLineEdit; // Создание поля ввода для веса ребра
    QLabel *label = new QLabel; // Создание метки
    label->setFrameStyle(QFrame::Box | QFrame::Plain); // Установка стиля рамки для метки (не используется)
    QPushButton *okButton = new QPushButton(tr("Принять")); // Создание кнопки "OK"

    QGridLayout *layout = new QGridLayout; // Создание сетки для компоновки виджетов
    layout->addWidget(new QLabel(tr("Начальная вершина:")), 0, 0); // Добавление метки для поля ввода начальной вершины
    layout->addWidget(input1, 0, 1); // Добавление поля ввода для начальной вершины
    layout->addWidget(new QLabel(tr("Конечная вершина:")), 1, 0); // Добавление метки для поля ввода конечной вершины
    layout->addWidget(input2, 1, 1); // Добавление поля ввода для конечной вершины
    layout->addWidget(new QLabel(tr("Вес:")), 2, 0); // Добавление метки для поля ввода веса ребра
    layout->addWidget(input3, 2, 1); // Добавление поля ввода для веса ребра
    layout->addWidget(okButton, 3, 1, Qt::AlignRight); // Добавление кнопки "OK" в сетку, выравнивание справа
    layout->setSizeConstraint(QLayout::SetFixedSize); // Установка фиксированного размера для сетки
    window->setLayout(layout); // Установка созданной сетки в качестве макета для виджета
    window->setWindowTitle("Добавить вес"); // Установка заголовка окна

    // Установка обработчика для сигнала нажатия кнопки без автоматического закрытия окна
    connect(okButton, &QPushButton::clicked, this, [this](){ emit addEdgeSignal(); });

    window->show(); // Отображение окна
}

void Graph::addEdgeSignal(){
    int srcIndex = input1->text().toInt(); // Получение начальной вершины из поля ввода (преобразование в целое число)
    int destIndex = input2->text().toInt(); // Получение конечной вершины из поля ввода (преобразование в целое число)
    double edgeWeight = input3->text().toDouble(); // Получение веса ребра из поля ввода (преобразование в число с плавающей точкой)
    window->close(); // Закрытие окна

    if(srcIndex >= vertexList.size() || destIndex >= vertexList.size() || edgeWeight <= 0){
        return; // Проверка условий: прерывание, если индексы выходят за пределы списка вершин или вес <= 0
    }
    insertEdge(srcIndex, destIndex, edgeWeight); // Вставка ребра с указанными параметрами в граф
}

void Graph::createEraseEdgeWindow(){
    window = new QWidget; // Создание нового виджета
    input1 = new QLineEdit; // Создание поля ввода для начальной вершины
    input2 = new QLineEdit; // Создание поля ввода для конечной вершины
    QLabel *label = new QLabel; // Создание метки (не используется)
    label->setFrameStyle(QFrame::Box | QFrame::Plain); // Установка стиля рамки для метки (не используется)
    QPushButton *okButton = new QPushButton(tr("Принять")); // Создание кнопки "Принять"

    QGridLayout *layout = new QGridLayout; // Создание сетки для компоновки виджетов
    layout->addWidget(new QLabel(tr("Начальная вершина:")), 0, 0); // Добавление метки для поля ввода начальной вершины
    layout->addWidget(input1, 0, 1); // Добавление поля ввода для начальной вершины
    layout->addWidget(new QLabel(tr("Конечная вершина:")), 1, 0); // Добавление метки для поля ввода конечной вершины
    layout->addWidget(input2, 1, 1); // Добавление поля ввода для конечной вершины
    layout->addWidget(okButton, 2, 1, Qt::AlignRight); // Добавление кнопки "Принять" в сетку, выравнивание справа
    layout->setSizeConstraint(QLayout::SetFixedSize); // Установка фиксированного размера для сетки
    window->setLayout(layout); // Установка созданной сетки в качестве макета для виджета
    window->setWindowTitle("Удалить ребро"); // Установка заголовка окна

    connect(okButton, &QPushButton::clicked, this, &Graph::eraseEdgeSignal); // Устанавливается соединение между сигналом нажатия кнопки и слотом eraseEdgeSignal данного объекта
    window->show(); // Отображение окна
}

//удаление ребра по пользовательским данным
void Graph::eraseEdgeSignal(){
    int srcIndex = input1->text().toInt(); // Получаем целочисленное значение из поля ввода input1
    int destIndex = input2->text().toInt(); // Получаем целочисленное значение из поля ввода input2
    window->close(); // Закрываем окно
    if(srcIndex >= vertexList.size() || destIndex >= vertexList.size()){ // Проверяем, что индексы находятся в пределах размера списка вершин
        return; // Если индексы выходят за пределы, просто завершаем метод
    }
    eraseEdge(srcIndex, destIndex); // Вызываем метод eraseEdge() для удаления ребра между указанными вершинами
}

void Graph::createUpdateWeightWindow(){
    window = new QWidget; // Создание нового виджета
    input1 = new QLineEdit; // Создание поля ввода для начальной вершины
    input2 = new QLineEdit; // Создание поля ввода для конечной вершины
    input3 = new QLineEdit; // Создание поля ввода для нового веса
    QLabel *label = new QLabel; // Создание метки (не используется)
    label->setFrameStyle(QFrame::Box | QFrame::Plain); // Установка стиля рамки для метки (не используется)
    QPushButton *okButton = new QPushButton(tr("Принять")); // Создание кнопки "Принять"

    QGridLayout *layout = new QGridLayout; // Создание сетки для компоновки виджетов
    layout->addWidget(new QLabel(tr("Начальная вершина:")), 0, 0); // Добавление метки для поля ввода начальной вершины
    layout->addWidget(input1, 0, 1); // Добавление поля ввода для начальной вершины
    layout->addWidget(new QLabel(tr("Конечная вершина:")), 1, 0); // Добавление метки для поля ввода конечной вершины
    layout->addWidget(input2, 1, 1); // Добавление поля ввода для конечной вершины
    layout->addWidget(new QLabel(tr("Новый вес")), 2, 0); // Добавление метки для поля ввода нового веса
    layout->addWidget(input3, 2, 1); // Добавление поля ввода для нового веса
    layout->addWidget(okButton, 3, 1, Qt::AlignRight); // Добавление кнопки "Принять" в сетку, выравнивание справа
    layout->setSizeConstraint(QLayout::SetFixedSize); // Установка фиксированного размера для сетки
    window->setLayout(layout); // Установка созданной сетки в качестве макета для виджета
    window->setWindowTitle("Изменить вес"); // Установка заголовка окна

    connect(okButton, &QPushButton::clicked, this, &Graph::updateWeightSignal); // Устанавливается соединение между сигналом нажатия кнопки и слотом updateWeightSignal данного объекта
    window->show(); // Отображение окна
}

//обновление веса
void Graph::updateWeightSignal() {
    int srcIndex = input1->text().toInt(); // Получаем целочисленное значение из поля ввода input1
    int destIndex = input2->text().toInt(); // Получаем целочисленное значение из поля ввода input2
    double edgeWeight = input3->text().toDouble(); // Получаем числовое значение из поля ввода input3
    window->close(); // Закрываем окно
    if (srcIndex >= vertexList.size() || destIndex >= vertexList.size() || edgeWeight <= 0) {
        return; // Проверяем, что индексы и вес находятся в допустимых пределах
    }
    updateWeight(srcIndex, destIndex, edgeWeight); // Вызываем метод updateWeight с передачей индексов и веса
}

void Graph::createDFSWindow(){
    window = new QWidget; // Создание нового виджета
    input1 = new QLineEdit; // Создание поля ввода
    QLabel *label = new QLabel; // Создание метки
    label->setFrameStyle(QFrame::Box | QFrame::Plain); // Установка стиля рамки для метки
    QPushButton *okButton = new QPushButton(tr("Принять")); // Создание кнопки "Принять"

    QGridLayout *layout = new QGridLayout; // Создание сетки для компоновки виджетов
    layout->addWidget(new QLabel(tr("Начальная вершина:")), 0, 0); // Добавление метки для ввода индекса начальной вершины
    layout->addWidget(input1, 0, 1); // Добавление поля ввода для индекса начальной вершины
    layout->addWidget(okButton, 1, 1, Qt::AlignRight); // Добавление кнопки "Принять" в сетку, выравнивание справа
    layout->setSizeConstraint(QLayout::SetFixedSize); // Установка фиксированного размера для сетки
    window->setLayout(layout); // Установка созданной сетки в качестве макета для виджета
    window->setWindowTitle("Обход в глубину"); // Установка заголовка окна

    connect(okButton, &QPushButton::clicked, this, &Graph::dfsSignal); // Устанавливается соединение между сигналом нажатия кнопки и слотом dfsSignal данного объекта
    window->show(); // Отображение окна
}

void Graph::dfsSignal(){
    int index = input1->text().toInt(); // Получаем целочисленное значение из поля ввода input1
    window->close(); // Закрываем окно
    if(index >= vertexList.size()){ // Проверяем, что индекс находится в пределах размера списка вершин
        return; // Если индекс выходит за пределы, просто завершаем метод
    }
    dfs(index); // Выполняем обход в глубину (DFS) с начальной вершиной, соответствующей индексу
}
//окно обхода в ширину
void Graph::createBFSWindow(){
    window = new QWidget; // Создание нового виджета
    input1 = new QLineEdit; // Создание поля ввода
    QLabel *label = new QLabel; // Создание метки
    label->setFrameStyle(QFrame::Box | QFrame::Plain); // Установка стиля рамки для метки
    QPushButton *okButton = new QPushButton(tr("Принять")); // Создание кнопки "Принять"

    QGridLayout *layout = new QGridLayout; // Создание сетки для компоновки виджетов
    layout->addWidget(new QLabel(tr("Начальная вершина:")), 0, 0); // Добавление метки для ввода начальной вершины
    layout->addWidget(input1, 0, 1); // Добавление поля ввода для начальной вершины
    layout->addWidget(okButton, 1, 1, Qt::AlignRight); // Добавление кнопки "Принять" в сетку, выравнивание справа
    layout->setSizeConstraint(QLayout::SetFixedSize); // Установка фиксированного размера для сетки
    window->setLayout(layout); // Установка созданной сетки в качестве макета для виджета
    window->setWindowTitle("Обход в ширину"); // Установка заголовка окна

    connect(okButton, &QPushButton::clicked, this, &Graph::bfsSignal); // Устанавливается соединение между сигналом нажатия кнопки и слотом bfsSignal данного объекта
    window->show(); // Отображение окна
}

//окно Дейкстры
void Graph::createDijkstraWindow()
{
    window = new QWidget; // Создание нового виджета
    input1 = new QLineEdit; // Создание поля ввода
    QLabel *label = new QLabel; // Создание метки
    label->setFrameStyle(QFrame::Box | QFrame::Plain); // Установка стиля рамки для метки
    QPushButton *okButton = new QPushButton(tr("Принять")); // Создание кнопки "Принять"

    QGridLayout *layout = new QGridLayout; // Создание сетки для компоновки виджетов
    layout->addWidget(new QLabel(tr("Начальная вершина:")), 0, 0); // Добавление метки для ввода начальной вершины
    layout->addWidget(input1, 0, 1); // Добавление поля ввода для начальной вершины
    layout->addWidget(okButton, 1, 1, Qt::AlignRight); // Добавление кнопки "Принять" в сетку, выравнивание справа
    layout->setSizeConstraint(QLayout::SetFixedSize); // Установка фиксированного размера для сетки
    window->setLayout(layout); // Установка созданной сетки в качестве макета для виджета
    window->setWindowTitle("Алгоритм Дейкстры"); // Установка заголовка окна

    connect(okButton, &QPushButton::clicked, this, &Graph::dijkstraSignal); // Устанавливается соединение между сигналом нажатия кнопки и слотом dijkstraSignal данного объекта
    window->show(); // Отображение окна
}

void Graph::createTSPWindow()
{
    window = new QWidget; // Создание нового виджета
    input1 = new QLineEdit; // Создание поля ввода
    QLabel *label  = new QLabel; // Создание метки
    label->setFrameStyle(QFrame::Box | QFrame::Plain); // Установка стиля рамки для метки
    QPushButton *okButton = new QPushButton(tr("Принять")); // Создание кнопки "Принять"

    QGridLayout *layout = new QGridLayout; // Создание сетки для компоновки виджетов
    layout->addWidget(new QLabel(tr("Начальная вершина:")), 0, 0); // Добавление метки для ввода начальной вершины
    layout->addWidget(input1, 0, 1); // Добавление поля ввода для начальной вершины
    layout->addWidget(okButton, 1, 1, Qt::AlignRight); // Добавление кнопки "Принять" в сетку, выравнивание справа
    layout->setSizeConstraint(QLayout::SetFixedSize); // Установка фиксированного размера для сетки
    window->setLayout(layout); // Установка созданной сетки в качестве макета для виджета
    window->setWindowTitle("Задача Коммивояжера"); // Установка заголовка окна

    connect(okButton, &QPushButton::clicked, this, &Graph::TSPSignal); // Устанавливается соединение между сигналом нажатия кнопки и слотом dijkstraSignal данного объекта
    window->show(); // Отображение окна
}

//обход в ширину
void Graph::bfsSignal(){
    int index = input1->text().toInt(); // Получаем целочисленное значение из поля ввода input1
    window->close();// Закрываем окно
    if(index >= vertexList.size()){// Проверяем, что индекс находится в пределах размера списка вершин
        return;// Если индекс выходит за пределы, просто завершаем метод
    }
    bfs(index);// Выполняем обход в ширину с начальной вершиной, соответствующей индексу
}

int Graph::dijkstraSignal()
{
    int index=input1->text().toInt();// Получаем целочисленное значение из поля ввода input1
    window->close();// Закрываем окно
    if(index >= vertexList.size()){// Проверяем, что индекс находится в пределах размера списка вершин
        return -1;// Если индекс выходит за пределы, возвращаем -1
    }
    return index;// Возвращаем индекс для дальнейшего использования
}


int Graph::TSPSignal()
{
    int index=input1->text().toInt();// Получаем целочисленное значение из поля ввода input1
    window->close();// Закрываем окно
    if(index >= vertexList.size()){// Проверяем, что индекс находится в пределах размера списка вершин
        return -1;// Если индекс выходит за пределы, возвращаем -1
    }
    return index;// Возвращаем индекс для дальнейшего использования
}
