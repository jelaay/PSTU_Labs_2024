#include "serialreader.h"
#include <QDebug>
#include <QStringList>

SerialReader::SerialReader(QObject *parent) :
    QObject(parent),
    serial(new QSerialPort(this)),
    m_lastError("")
{
}

SerialReader::~SerialReader()
{
    disconnectPort();
}

void SerialReader::setError(const QString &error)
{
    m_lastError = error;
    emit errorOccurred(error);
    qWarning() << error;
}

bool SerialReader::connectToPort(const QString &portName) //Настраивает параметры порта, открывает его в режиме чтения
{
    if (isConnected()) {
        setError("Already connected to " + serial->portName());
        return false;
    }

    if (portName.isEmpty()) {
        setError("Port name is empty");
        return false;
    }

    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (!serial->open(QIODevice::ReadOnly)) {
        setError("Failed to open port " + portName + ": " + serial->errorString());
        return false;
    }

    connect(serial, &QSerialPort::readyRead, this, &SerialReader::handleReadyRead);
    emit connectionStatusChanged(true);
    return true;
}

void SerialReader::disconnectPort()
{
    if (isConnected()) {
        serial->close();
        emit connectionStatusChanged(false);
    }
}

bool SerialReader::isConnected() const
{
    return serial->isOpen();
}

QString SerialReader::currentPort() const
{
    return serial->portName();
}

QString SerialReader::lastError() const
{
    return m_lastError;
}

void SerialReader::handleReadyRead() //Читает строку из порта, передает данные в парс
{
    try {
        while (serial->canReadLine()) {
            QString line = QString::fromUtf8(serial->readLine()).trimmed();
            parseArduinoData(line);
        }
    } catch (const std::exception &e) {
        setError("Read error: " + QString(e.what()));
    }
}

void SerialReader::parseArduinoData(const QString &data) { //Ожидает строку, разбивает её на части, отправляет их
    qDebug() << "Raw data:" << data; // Для отладки

    if (data.contains("Освещенность:") && data.contains("Подогрев:")) {
        QString simplified = data.simplified(); // Удаляем лишние пробелы
        QStringList parts = simplified.split(',');

        if (parts.size() >= 3) {
            try {
                // Парсинг освещенности
                int light = parts[0].split(':')[1].trimmed().toInt();

                // Парсинг температуры
                float temp = parts[1].split(':')[1].trimmed().split(' ')[0].toFloat();

                // Парсинг состояния подогрева (учёт регистра)
                QString heatingStr = parts[2].split(':')[1].trimmed().toUpper();
                bool heating = (heatingStr == "ON" || heatingStr == "ВКЛ");

                qDebug() << "Parsed - Temp:" << temp << "Light:" << light << "Heating:" << heating;
                emit dataReceived(temp, light, heating);
            }
            catch (...) {
                setError("Ошибка парсинга данных: " + data);
            }
        }
    }
}
