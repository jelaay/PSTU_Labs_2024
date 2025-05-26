#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "tree.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QString>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_create1_clicked();

    void on_pushButton_5_clicked();

    void on_print_clicked();
    void showTree(tree* tree, int x, int y);

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    QTextEdit *outputTextEdit;
    QGraphicsScene *Win;
    QGraphicsEllipseItem *ellips;
    QGraphicsLineItem *line;
    QGraphicsTextItem *text;
};
#endif // MAINWINDOW_H
