#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdio>
#include <QtSerialPort>
#include <QSerialPortInfo>

QSerialPort serial;


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

}


void MainWindow::on_refreshButon_clicked()
{
    //Lista as portas disponíveis e seta cada uma como um item do comboBox
    const auto portsList = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &specificPort : portsList)
        ui->comboBox_comPort->addItem(specificPort.portName());
}


void MainWindow::on_spinBox_fan1_valueChanged(int arg1)
{
    char label[64];
    sprintf_s(label, 64, "%d", arg1);
    ui->label_fan1->setText(label);
}

