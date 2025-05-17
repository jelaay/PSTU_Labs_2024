#include "roofheater.h"
#include "ui_mainwindow.h"
#include "serialreader.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>

RoofHeater::RoofHeater(QWidget *parent) : //Инициализирует UI, Создает объекты
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    serialReader(new SerialReader(this)),
    connectionTimer(new QTimer(this))
{
    ui->setupUi(this);
    setupUI();
    setupConnections();
    populatePorts();

    connectionTimer->setInterval(5000);
    connectionTimer->start();
}
void RoofHeater::setupUI() //Блокирует кнопку "Отключить" при старте, Активирует кнопку "Подключить
{
    ui->disconnectButton->setEnabled(false);
    ui->connectButton->setEnabled(true);
}
void RoofHeater::setupConnections() //связывает Кнопки и слоты,
{
    connect(ui->refreshPortsButton, &QPushButton::clicked, this, &RoofHeater::refreshPortList);
    connect(ui->connectButton, &QPushButton::clicked, this, &RoofHeater::connectToArduino);
    connect(ui->disconnectButton, &QPushButton::clicked, this, &RoofHeater::disconnectFromArduino);
    connect(serialReader, &SerialReader::dataReceived, this, &RoofHeater::updateData);
    connect(serialReader, &SerialReader::connectionStatusChanged, this, &RoofHeater::onConnectionStatusChanged);
    connect(connectionTimer, &QTimer::timeout, this, &RoofHeater::checkConnection);
    connect(serialReader, &SerialReader::errorOccurred, this, [this](const QString &error) {
            ui->statusbar->showMessage("Ошибка: " + error, 5000);
            qDebug() << "Ошибка связи:" << error;
        });
        connect(serialReader, &SerialReader::dataReceived, this, [](float t, int l, bool h) {
            qDebug() << "Данные - Темп:" << t << "Свет:" << l << "Нагрев:" << h;
        });
}

void RoofHeater::populatePorts()
{
    ui->portComboBox->clear();
    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports) {
        QString portInfo = QString("%1 (%2)").arg(port.portName(), port.description());
        ui->portComboBox->addItem(portInfo, port.portName());
    }
    if (ports.isEmpty()) {
        ui->portComboBox->addItem("No ports available", "");
        ui->connectButton->setEnabled(false);
    }
}

void RoofHeater::refreshPortList()
{
    populatePorts();
    showStatusMessage("Port list refreshed");
}

void RoofHeater::connectToArduino() //Берет выбранный порт, подключается через порт
{
    QString portName = ui->portComboBox->currentData().toString();
    if (portName.isEmpty()) {
        showStatusMessage("No port selected", true);
        return;
    }

    if (!serialReader->connectToPort(portName)) {
        showStatusMessage("Connection failed: " + serialReader->lastError(), true);
    }
}

void RoofHeater::disconnectFromArduino()
{
    serialReader->disconnectPort();
    showStatusMessage("Disconnected from Arduino");
}

void RoofHeater::onConnectionStatusChanged(bool connected) // Блокирует/разблокирует кнопки и комбобокс портов
{
    ui->connectButton->setEnabled(!connected);
    ui->disconnectButton->setEnabled(connected);
    ui->portComboBox->setEnabled(!connected);
    if (connected) {
        showStatusMessage("Connected to " + serialReader->currentPort());
    }
}

void RoofHeater::checkConnection() //Проверяет, активен ли порт.
{
    if (serialReader->isConnected()) {
        // Проверка активности соединения
        if (!serialReader->currentPort().isEmpty() &&
            !QSerialPortInfo(serialReader->currentPort()).isBusy()) {
            showStatusMessage("Connection lost", true);
            disconnectFromArduino();
        }
    }
}

void RoofHeater::updateData(float temp, int light, bool heating) { //Обновляет значения на экране, Логирует данные в консоль
    ui->temperatureLabel->setText(QString("Температура: %1 °C").arg(temp, 0, 'f', 1));
    ui->lightLabel->setText(QString("Освещенность: %1%").arg(light));
    ui->heatingLabel->setText(heating ? "ON" : "OFF");
    ui->heatingLabel->setStyleSheet(heating ? "color: red; font-weight: bold;" : "color: green;");
    qDebug() << "Данные получены. Подогрев:" << (heating ? "ON" : "OFF");
}
void RoofHeater::showStatusMessage(const QString &message, bool isError)//Выводит сообщение в статусную строку
{
    if (isError) {
        ui->statusbar->setStyleSheet("color: red;");
        qWarning() << "Error:" << message;
    } else {
        ui->statusbar->setStyleSheet("");
        qDebug() << "Info:" << message;
    }
    ui->statusbar->showMessage(message, 5000);
}

RoofHeater::~RoofHeater()
{
    delete serialReader;
    delete ui;
}
