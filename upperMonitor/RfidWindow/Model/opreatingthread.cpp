#include "opreatingthread.h"

#include "rfidopreatingmachine.h"
#include "rfidcardreadinfo.h"

OpreatingThread::OpreatingThread(QString comName):
    QThread(),
    currentCardID(""),
    preCardID("")
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
        RfidCardReadInfo rfidCardReadInfo(machine->readData(), currentCardID, QDateTime::currentDateTime());
        emit sendCardMessage(rfidCardReadInfo);
    }
}

void OpreatingThread::setIsRun(bool value)
{
    isRun = value;
}

