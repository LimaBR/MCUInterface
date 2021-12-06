#ifndef MCU_H
#define MCU_H
#include <QtSerialPort>
#include <QSerialPortInfo>

class MCU
{
public:
    MCU(QSerialPort* _serial);
    virtual ~MCU();
    void dataAvailable(QSerialPort* _serial);
    void askForTypes();
    void sendData(std::vector<int> data);
    std::vector<int> typesOut;
    std::vector<int> typesIn;
private:
    QSerialPort* serial;
    char recvBuffer[1024];
    char sendBuffer[1024];
    std::vector<int> outputValues;
    int isOpen = 0;
};

#endif  // MCU_H
