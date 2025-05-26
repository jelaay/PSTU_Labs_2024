#ifndef TSP_H
#define TSP_H

#include <QMainWindow>
#include "glwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TSP; }
QT_END_NAMESPACE

class TSP : public QMainWindow
{
    Q_OBJECT

public:
    TSP(QWidget *parent = nullptr);
    ~TSP();
    GlWidget* openGlW;

private slots:
    void on_addTopButton_clicked();

    void on_delTopButton_clicked();

    void on_addOneWayEdgeButton_clicked();

    void on_addTwoWayEdgeButton_clicked();

    void on_calculateRouteButton_clicked();

    void on_clearButton_clicked();


private:
    Ui::TSP *ui;

};
#endif // TSP_H
