#include "rfidcardreadinfo.h"

RfidCardReadInfo::RfidCardReadInfo()
{
    this->data = "";
    this->cardID = "";
    this->dateTime = QDateTime::currentDateTime();
}

RfidCardReadInfo::RfidCardReadInfo(QString data, QString cardID, QDateTime dateTime)
{
    this->data = data;
    this->cardID = cardID;
    this->dateTime = dateTime;

}

RfidCardReadInfo::RfidCardReadInfo(const RfidCardReadInfo &rfidCardReadInfo)
{
    this->data = rfidCardReadInfo.getData();
    this->cardID = rfidCardReadInfo.getCardID();
    this->dateTime = rfidCardReadInfo.getDateTime();
}

RfidCardReadInfo::~RfidCardReadInfo()
{

}

QDateTime RfidCardReadInfo::getDateTime() const
{
    return dateTime;
}

QString RfidCardReadInfo::getCardID() const
{
    return cardID;
}

QString RfidCardReadInfo::getData() const
{
    return data;
}


