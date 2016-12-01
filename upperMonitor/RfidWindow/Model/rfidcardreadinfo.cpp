#include "rfidcardreadinfo.h"

RfidCardReadInfo::RfidCardReadInfo(QString data, QString cardID, QDate date)
{
    this->data = data;
    this->cardID = cardID;
    this->date = date;

}

QDate RfidCardReadInfo::getDate() const
{
    return date;
}

QString RfidCardReadInfo::getCardID() const
{
    return cardID;
}

QString RfidCardReadInfo::getData() const
{
    return data;
}


