#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tree.h"
#include <QMessageBox>

BinaryTree *mainTree = new BinaryTree;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Win = new QGraphicsScene(this);
    ui->Win->setScene(Win);
    Win->setSceneRect(280, 0, 1021, 541);
    outputTextEdit = new QTextEdit(this);
    outputTextEdit->setGeometry(30, 260, 211, 121);
}

MainWindow::~MainWindow() {delete ui;}

void MainWindow::showTree(tree* tree, int x, int y) {
    QRadialGradient color(30, 30, 30);
    color.setColorAt(0, Qt::black);   // Оранжевый в центре  // Розовый на краю
    QBrush brush(color);
    QPen pen(Qt::black);
    pen.setWidth(2);

    if (tree != nullptr) {
    showTree(tree->left, tree->x, tree->y);
    ellips = Win->addEllipse(tree->x, tree->y, 30, 30, pen, brush);
    QFont font("Arial", 10, QFont::Bold);
    text = Win->addText(QString::number(tree->data), font );

    text->setDefaultTextColor(QColor("white"));
    text->setPos(ellips->boundingRect().center().x() - text->boundingRect().width()/2, ellips->boundingRect().center().y() - text->boundingRect().height()/2);
    line = Win->addLine(x+15, y+30, tree->x+15, tree->y, pen);
    showTree(tree->right, tree->x, tree->y);
}
    }

void MainWindow::on_create1_clicked() {
    QString data = ui->ROOT->text();
    if(ui->rootRadio->isChecked()) {
        mainTree->createTree(data.toInt());
    }
    if (ui->addRadio_2->isChecked()) {
        mainTree->insert(mainTree->BinTree,data.toInt(), 790, 0, 150);
    }
    if (ui->delRadio->isChecked()) {
        mainTree->deleteElem(mainTree->BinTree, data.toInt());
        Win->clear();
    }
    ui->ROOT->clear();
}

void MainWindow::on_pushButton_5_clicked()
{
    Win->clear();
    delete mainTree;
}


void MainWindow::on_print_clicked()
{
    Win->clear();
    showTree(mainTree->BinTree, 790, 0);

}


void MainWindow::on_pushButton_6_clicked()
{
    QString out;
    mainTree->printPreOrdered(mainTree->BinTree, out);
    outputTextEdit->setText(out);
}

void MainWindow::on_pushButton_8_clicked()
{
    QString out;
    mainTree->printInOrdered(mainTree->BinTree, out);
    outputTextEdit->setText(out);
}


void MainWindow::on_pushButton_7_clicked()
{
    QString out;
    mainTree->printPostOrdered(mainTree->BinTree, out);
    outputTextEdit->setText(out);
}

