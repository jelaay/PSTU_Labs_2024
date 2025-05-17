#include "roofheater.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //Создает объект QApplication (основа Qt-приложения)
    QFile styleFile(":/styles/dark.qss");
    if (styleFile.open(QIODevice::ReadOnly)) {
        a.setStyleSheet(styleFile.readAll());
        styleFile.close();
    }

    RoofHeater w;
    w.show(); //Создает и отображает главное окно
    return a.exec();
}
