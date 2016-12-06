#include "rfidcardreadinfo.h"

RfidCardReadInfo::RfidCardReadInfo()
{
    cardID = "";
    dateTime = QDateTime::currentDateTime();
}

RfidCardReadInfo::RfidCardReadInfo(QString cardData, const QString &cardID, const QDateTime &dateTime)
{
    this->commodity.setID(cardData.left(0));
    cardData.remove(0, 1);
    qDebug() << cardData;

    this->commodity.setName(cardData.left(1));
    cardData.remove(0, 2);
    qDebug() << cardData;

    this->commodity.setWeiget(cardData.left(0).toInt());
    cardData.remove(0, 1);
    qDebug() << cardData;

    this->commodity.setPrice(cardData.left(0).toInt());
    cardData.remove(0, 1);
    qDebug() << cardData;

    this->commodity.setSupplierName(cardData.left(0));
    cardData.remove(0, 1);
    qDebug() << cardData;

    this->commodity.setSupplierID(cardData.left(3));


    this->cardID = cardID;
    this->dateTime = dateTime;
}

RfidCardReadInfo::RfidCardReadInfo(const QString &cardID, const QDateTime &dateTime, const Commodity &commodityValue):
    commodity(commodityValue)
{
    this->cardID = cardID;
    this->dateTime = dateTime;
}


RfidCardReadInfo::RfidCardReadInfo(const RfidCardReadInfo &rfidCardReadInfo)
{
    this->cardID = rfidCardReadInfo.getCardID();
    this->dateTime = rfidCardReadInfo.getDateTime();
    this->commodity = rfidCardReadInfo.getCommodity();
}

RfidCardReadInfo::~RfidCardReadInfo()
{

}

QString RfidCardReadInfo::getCardID() const
{
    return cardID;
}

void RfidCardReadInfo::setCardID(const QString &value)
{
    cardID = value;
}

QDateTime RfidCardReadInfo::getDateTime() const
{
    return dateTime;
}

void RfidCardReadInfo::setDateTime(const QDateTime &value)
{
    dateTime = value;
}

Commodity RfidCardReadInfo::getCommodity() const
{
    return commodity;
}

void RfidCardReadInfo::setCommodity(const Commodity &value)
{
    commodity.setID(value.getID());
    commodity.setName(value.getName());
    commodity.setWeiget(value.getWeiget());
    commodity.setPrice(value.getPrice());
    commodity.setSupplierName(value.getSupplierName());
    commodity.setSupplierID(value.getSupplierID());
}

QString RfidCardReadInfo::toString() const
{
    return QString(dateTime.toString() + "\n" + "卡号: " + cardID +
                   " 商品编号: " + commodity.getID() +
                   " 商品名称: " + commodity.getName() +
                   " 商品价格: " + QString::number(commodity.getPrice()) +
                   " 商品重量: " + QString::number(commodity.getWeiget()) +
                   " 供应商: " + commodity.getSupplierName() +
                   " 供应商编号: " + commodity.getSupplierID());
}


///**
// * 数据变为Json
// */
//void RfidCardReadInfo::toJson()
//{
//    QJsonObject json;
//    json.insert("data", QJsonValue(data));
//    json.insert("cardID", QJsonValue(cardID));
//    json.insert("time", QJsonValue(dateTime.toString()));

//    QJsonDocument document;
//    document.setObject(json);
//    byteArrayFromJson = document.toJson(QJsonDocument::Compact);

//    qDebug() << byteArrayFromJson;
//}



