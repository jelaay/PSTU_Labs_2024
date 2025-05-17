QT += core gui serialport widgets #Подключает модули Qt: ядро, GUI, работу с COM-портами, виджеты.
CONFIG += c++17

TARGET = RoofHeater #Имя исполняемого файла.
TEMPLATE = app

SOURCES += main.cpp \ #Списки исходников, заголовков и UI-файлов.
           roofheater.cpp \
           serialreader.cpp

HEADERS += roofheater.h \
           serialreader.h

FORMS += mainwindow.ui

DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_CXXFLAGS += -Wall -Wextra -Werror

