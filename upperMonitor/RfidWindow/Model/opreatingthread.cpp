#include "opreatingthread.h"
#include "rfidopreatingmachine.h"

OpreatingThread::OpreatingThread(QString comName):
    QThread()
{
    comName.remove("COM");
    machine = new RfidOpreatingMachine(comName.toInt());
    isRun = true;
}

OpreatingThread::~OpreatingThread()
{
    if(machine)
        delete machine;
    machine = 0;
}

void OpreatingThread::run()
{
    qDebug() << "come";
    while (isRun) {
        readInfo();
        msleep(500);
    }
}

void OpreatingThread::readInfo()
{
    machine->findCard();
    machine->anticoll();
    machine->selectCard();
    machine->authentication();
    qDebug() << machine->readData();
}

void OpreatingThread::setIsRun(bool value)
{
    isRun = value;
}

