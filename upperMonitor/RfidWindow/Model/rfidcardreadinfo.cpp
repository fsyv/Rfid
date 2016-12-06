#include "rfidcardreadinfo.h"

RfidCardReadInfo::RfidCardReadInfo()
{
    this->data = "";
    this->cardID = "";
    this->dateTime = QDateTime::currentDateTime();

    toJson();
}

RfidCardReadInfo::RfidCardReadInfo(QString data, QString cardID, QDateTime dateTime)
{
    this->data = data;
    this->cardID = cardID;
    this->dateTime = dateTime;

    toJson();
}

RfidCardReadInfo::RfidCardReadInfo(const RfidCardReadInfo &rfidCardReadInfo)
{
    byteArrayFromJson = rfidCardReadInfo.getByteArrayFromJson();
}

RfidCardReadInfo::~RfidCardReadInfo()
{

}

QByteArray RfidCardReadInfo::getByteArrayFromJson() const
{
    return byteArrayFromJson;
}

/**
 * 数据变为Json
 */
void RfidCardReadInfo::toJson()
{
    QJsonObject json;
    json.insert("data", QJsonValue(data));
    json.insert("cardID", QJsonValue(cardID));
    json.insert("time", QJsonValue(dateTime.toString()));

    QJsonDocument document;
    document.setObject(json);
    byteArrayFromJson = document.toJson(QJsonDocument::Compact);

    qDebug() << byteArrayFromJson;
}



