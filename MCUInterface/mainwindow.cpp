#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdio>
#include <QtSerialPort>
#include <QSerialPortInfo>

QSerialPort serial;
QString serialName;
char recvBuffer[64];
char sendBuffer[64];
uint32_t fanSpeed[4];
char fanText[4][64];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{
    sprintf_s(sendBuffer, 64, "Y%08lX-%08lX-%08lX-%08lX-Z"
              , ui->spinBox_fan1->value()
              , ui->spinBox_fan2->value()
              , ui->spinBox_fan3->value()
              , ui->spinBox_fan4->value());
    serial.write(sendBuffer, 64);
}

void MainWindow::on_refreshButton_clicked()
{
    //Lista as portas disponíveis e seta cada uma como um item do comboBox
    const auto portsList = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &specificPort : portsList)
        ui->comboBox_comPort->addItem(specificPort.portName());
}


void MainWindow::on_spinBox_fan1_valueChanged(int arg1)
{
    /*char label[64];
    sprintf_s(label, 64, "%d", arg1);
    ui->label_fan1->setText(label);*/
}


void MainWindow::on_comboBox_comPort_currentTextChanged(const QString &arg1)
{
    serialName = arg1;
    serial.close();
}


void MainWindow::on_openButton_clicked()
{
    serial.setPortName(serialName);
    serial.open(QIODevice::ReadWrite);
    connect(&serial, &QSerialPort::readyRead, this, &MainWindow::serialSlot);
}

void MainWindow::serialSlot(){
    serial.read(recvBuffer, 64);
    sscanf_s(recvBuffer, "W%08lX-%08lX-%08lX-%08lX-X", &fanSpeed[0], &fanSpeed[1], &fanSpeed[2], &fanSpeed[3]);
    for (int i=0; i<4; i++){
            sprintf_s(fanText[i], 64, "%ld", fanSpeed[i]);
    }
    ui->label_fan1->setText(fanText[0]);
    ui->label_fan2->setText(fanText[1]);
    ui->label_fan3->setText(fanText[2]);
    ui->label_fan4->setText(fanText[3]);
}
