#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdio>

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

}


void MainWindow::on_spinBox_fan1_valueChanged(int arg1)
{
    char label[64];
    sprintf_s(label, 64, "%d", arg1);
    ui->label_fan1->setText(label);
}

