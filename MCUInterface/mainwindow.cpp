#include "mainwindow.h"
#include "ui_mainwindow.h"

MCU* mcu0;

/**
 * @brief MainWindow::MainWindow
 * @details Class constructor.
 * @param parent Parent class
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

/**
 * @brief MainWindow::~MainWindow
 * @details Class destructor.
 */

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::on_sendButton_clicked
 * @details Callback for Send button clicked. formats data to send into a vector and calls sendData.
 */

void MainWindow::on_sendButton_clicked()
{
    std::vector<int> sendVector;
    for(int i=0; i<inputContent.size(); i++){
        sendVector.push_back(inputContent[i]->value());
    }
    mcu0->sendData(sendVector);
}

/**
 * @brief MainWindow::on_refreshButton_clicked
 * @details Callback for Refresh button clicked. Refreshes the lists of available serial ports and populates the combo box.
 */

void MainWindow::on_refreshButton_clicked()
{
    //Lista as portas disponíveis e seta cada uma como um item do comboBox
    const auto portsList = QSerialPortInfo::availablePorts();
    ui->comPort->clear();
    for (const QSerialPortInfo &specificPort : portsList)
        ui->comPort->addItem(specificPort.portName());
}

/**
 * @brief MainWindow::on_comPort_currentTextChanged
 * @details Callback for comPort combo box value changed. Updates the serialName attribute with the new port.
 * @param arg1 The name of the serial port selected
 */

void MainWindow::on_comPort_currentTextChanged(const QString &arg1)
{
    serialName = arg1;
}

/**
 * @brief MainWindow::on_openButton_clicked
 * @details Callback for Open button clicked. Opens the serial port, allocates MCU object and ask MCU for data types.
 */

void MainWindow::on_openButton_clicked()
{
    //TODO: Não fazer nada se já estiver aberto
    serial.close();
    serial.setPortName(serialName);
    serial.setBaudRate(1000000); //Baud rate 1Mbps
    bool ok = serial.open(QIODevice::ReadWrite);
    //TODO: Verificar se a porta realmente foi aberta
    mcu0 = new MCU(&serial);
    connect(&serial, &QSerialPort::readyRead, this, &MainWindow::serialSlot);
    mcu0->askForTypes();
}

/**
 * @brief MainWindow::on_closeButton_clicked
 * @details Callback for Close port button clicked. Closes the serial port, cleans the GUI and frees allocated memory.
 */

void MainWindow::on_closeButton_clicked()
{
    //TODO: Forma mais elegante de remover tudo
    for(QLabel* element : outputName){
        ui->verticalLayout_output->removeWidget(element);
        delete element;
    }
    outputName.clear();
    for(QFrame* element : outputFrame){
        ui->verticalLayout_output->removeWidget(element);
        delete element;
    }
    outputFrame.clear();
    for(QLabel* element : outputContent){
        ui->verticalLayout_output->removeWidget(element);
        delete element;
    }
    outputContent.clear();
    for(QLabel* element : inputName){
        ui->verticalLayout_input->removeWidget(element);
        delete element;
    }
    inputName.clear();
    for(QSpinBox* element : inputContent){
        ui->verticalLayout_input->removeWidget(element);
        delete element;
    }
    inputContent.clear();
    if (serial.isOpen()){
        disconnect(&serial, &QSerialPort::readyRead, this, &MainWindow::serialSlot);
        delete mcu0;
        serial.close();
    }
}

/**
 * @brief MainWindow::setupMCUWidget
 * @details Setup the GUI with the spinboxes and labels for the inputs and outputs.
 */

void MainWindow::setupMCUWidget(){
    //Codigo para setup da interface
    for(int type : mcu0->typesOut){
        char label[16];
        sprintf_s(label, 16, "Out %d", type);
        outputName.push_back(new QLabel(label));
        outputFrame.push_back(new QFrame());
        outputContent.push_back(new QLabel("-", outputFrame.back()));
        //TODO: Tamanho dos widgets
        outputContent.back()->setFrameShape(QFrame::Box);
        outputContent.back()->setFrameShadow(QFrame::Sunken);
        outputContent.back()->setLineWidth(1);
        outputContent.back()->setMidLineWidth(0);
        ui->verticalLayout_output->addWidget(outputName.back());
        ui->verticalLayout_output->addWidget(outputContent.back());
    }
    for(int type : mcu0->typesIn){
        char label[16];
        sprintf_s(label, 16, "In %d", type);
        inputName.push_back(new QLabel(label));
        inputContent.push_back(new QSpinBox());
        //TODO: Tamanho dos widgets
        ui->verticalLayout_input->addWidget(inputName.back());
        ui->verticalLayout_input->addWidget(inputContent.back());
    }
}

/**
 * @brief MainWindow::setOutputValues
 * @details Updates the GUI with the values output from the MCU
 * @param values Values output from the MCU to be updated on the GUI
 */

void MainWindow::setOutputValues(std::vector<int> values){
    for(int i=0; i<values.size(); i++){
        outputContent[i]->setText(QString::number(values[i]));
    }
}

/**
 * @brief MainWindow::serialSlot
 * @details Callback when data is available on the serial port.
 */

void MainWindow::serialSlot(){
    mcu0->dataAvailable(&serial);
}
