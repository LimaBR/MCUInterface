#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mcu.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <QtSerialPort>
#include <QSerialPortInfo>
#include <QSpinBox>
#include <Qlabel>
#include <QFrame>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupMCUWidget();
    void setOutputValues(std::vector<int> values);

private slots:
    void on_sendButton_clicked();

    void on_refreshButton_clicked();

    void on_comPort_currentTextChanged(const QString &arg1);

    void on_openButton_clicked();

    void on_closeButton_clicked();

    void serialSlot();

private:
    Ui::MainWindow *ui;
    QSerialPort serial;
    QString serialName;
    std::vector<QLabel*> outputName;
    std::vector<QFrame*> outputFrame;
    std::vector<QLabel*> outputContent;
    std::vector<QLabel*> inputName;
    std::vector<QSpinBox*> inputContent;
};
#endif // MAINWINDOW_H
