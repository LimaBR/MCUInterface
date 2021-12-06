#include "mcu.h"
#include <mainwindow.h>

extern MainWindow* w;

MCU::MCU(QSerialPort* _serial) : serial(_serial){

}

MCU::~MCU(){

}

void MCU::dataAvailable(QSerialPort* _serial){
    //Dados disponíveis para leitura na porta serial
    serial->read(recvBuffer, 1024);
    if(recvBuffer[0] == 'T'){
        //Retorno dos tipos de entrada e saída
        typesOut.clear();
        typesIn.clear();
        for(int i=1; ; i+=9){
            if(recvBuffer[i] == 'O'){
                int x;
                sscanf_s(&recvBuffer[i+1], "%8lX", &x);
                typesOut.push_back(x);
            }else if(recvBuffer[i] == 'I'){
                int x;
                sscanf_s(&recvBuffer[i+1], "%8lX", &x);
                typesIn.push_back(x);
            }else if(recvBuffer[i] == 'U'){
                break;
            }else{
                //error
                break;
            }
        }
        w->setupMCUWidget();
        isOpen = 1;
    }else if(recvBuffer[0] == 'W' && isOpen){
        outputValues.clear();
        for(int i=1; ; i+=9){
            if(recvBuffer[i] == '-'){
                int x;
                sscanf_s(&recvBuffer[i+1], "%8lX", &x);
                outputValues.push_back(x);
            }else if(recvBuffer[i] == 'X'){
                break;
            }else{
                //error
                break;
            }
        }
        w->setOutputValues(outputValues);
    }
}

void MCU::sendData(std::vector<int> data){
    int i;
    sendBuffer[0] = 'Y';
    for(i=0; i<data.size(); i++){
        sprintf(&sendBuffer[9*i + 1], "-%08lX", data[i]);
    }
    sendBuffer[9*i + 1] = 'Z';
    sendBuffer[9*i + 2] = 0;
    serial->write(sendBuffer, 9*i+3);
}

void MCU::askForTypes(){
    //Codigo para perguntar para o MCU sobre o formato da entrada e da saída
    serial->write("?types", 8);
}
