#ifndef SERIALREADER_H
#define SERIALREADER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialReader : public QObject
{
    Q_OBJECT
public:
    explicit SerialReader(QObject *parent = nullptr);
    ~SerialReader();

    bool connectToPort(const QString &portName); //Подключается к указанному порту
    void disconnectPort(); //Закрывает соединение
    bool isConnected() const; //Проверяет, открыт ли порт
    QString currentPort() const; //Возвращают текущий порт и последнюю ошибку
    QString lastError() const;

signals:
    void dataReceived(float temperature, int light, bool heating); //Отправляет данные от Arduino.
    void connectionStatusChanged(bool connected); //Уведомляет об изменении состояния подключения.
    void errorOccurred(const QString &error); //Отправляет сообщение об ошибке.

private slots:
    void handleReadyRead(); //Читает данные из порта.

private:
    QSerialPort *serial;
    QString m_lastError;
    void parseArduinoData(const QString &data); //Разбирает строку от Arduino.
    void setError(const QString &error); //Устанавливает текст ошибки.
};

#endif // SERIALREADER_H
