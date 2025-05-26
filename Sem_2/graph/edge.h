#ifndef EDGE_H
#define EDGE_H

#include <graph.h>
#include <vertex.h>
#include <QMainWindow>
#include <QGraphicsItem>
#include <QVector>
#include <QPointF>
#include <QGraphicsView>
#include <QWidget>
#include <QStyleOptionGraphicsItem>
#include <QKeyEvent>

//объявляем классы
class Vertex;
class Edge;
class Graph;

//класс ребра

class Edge : public QGraphicsItem {
private:
    Vertex *firstV, *secondV; //1 вершина, 2 вершина
    QPointF firstVPoint; //точка на вершине, где будет начинаться ребро
    QPointF secondVPoint; //точка на другой вершине, где закончится ребро
    qreal arrowSize = 10; //размер стрелки
    QString color; //цвет ребра
    double weight; //вес ребра
public:

    Edge(Vertex *source, Vertex *dest, double weight); //принимает указатель на 1 вершину, указатель на 2 вершину, вес
    ~Edge(); //деструктор
    void tuneEdge(); //корректируем и обновляем положение ребра и вершин
    Vertex *firstVertex() const; //вовзращаем указатель на начальную вершину
    Vertex *secondVertex() const; //возвращаем указатель на следующую вершину
    double getWeight(); //вовзращаем вес ребра
    void setWeight(double w); //установка веса ребра
    QString getColor(); //возвращаем цвет ребра
    void setColor(QString color); //устаналиваем цвет ребра

protected:
    //рисовка ребра
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
#endif // EDGE_H
