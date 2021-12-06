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
    std::vector<int> typesOut;
    std::vector<int> typesIn;
private:
    QSerialPort* serial;
    char recvBuffer[128];
};

#endif  // MCU_H
