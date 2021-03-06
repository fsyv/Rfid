#include "opreatingthread.h"

#include "rfidopreatingmachine.h"
#include "rfidcardreadinfo.h"

OpreatingThread::OpreatingThread(QString comName):
    QThread(),
    preCardID(""),
    currentCardID("")
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
    while (isRun) {
        readInfo();
        msleep(100);
    }
}

void OpreatingThread::readInfo()
{
    machine->findCard();
    currentCardID = machine->anticoll();

    if(currentCardID != QString("") && currentCardID != preCardID)
    {
        preCardID = currentCardID;
        machine->selectCard();
        machine->authentication();
        qDebug() << currentCardID;
        QString data = machine->readData();
        if(data != QString(""))
        {
            RfidCardReadInfo rfidCardReadInfo(data, currentCardID, QDateTime::currentDateTime());
            emit sendCardMessage(rfidCardReadInfo);
        }
    }
}

void OpreatingThread::setIsRun(bool value)
{
    isRun = value;
}

