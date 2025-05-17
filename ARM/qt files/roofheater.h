#ifndef ROOFHEATER_H
#define ROOFHEATER_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class SerialReader;

class RoofHeater : public QMainWindow
{
    Q_OBJECT
public:
    explicit RoofHeater(QWidget *parent = nullptr); //Конструктор: инициализирует UI и компоненты
    ~RoofHeater(); //Деструктор: освобождает ресурсы

private slots:
    void updateData(float temp, int light, bool heating); //Обновляет интерфейс на основе данных от Arduino.
    void refreshPortList(); //Обновляет список COM-портов
    void connectToArduino(); //Подключается к выбранному порту
    void disconnectFromArduino(); //Отключает Arduino
    void onConnectionStatusChanged(bool connected); //Обрабатывает изменение статуса подключения
    void checkConnection(); //Проверяет активность соединения по таймеру

private:
    Ui::MainWindow *ui;
    SerialReader *serialReader;
    QTimer *connectionTimer;

    void setupUI(); //Настраивает начальное состояние интерфейса
    void populatePorts(); //Связывает сигналы и слоты
    void showStatusMessage(const QString &message, bool isError = false); //Заполняет список доступных портов
    void setupConnections(); //Выводит сообщения в статусную строку
};

#endif // ROOFHEATER_H
