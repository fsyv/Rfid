#ifndef RFIDCARDREADINFO_H
#define RFIDCARDREADINFO_H

#include <QString>
#include <QDateTime>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "Controller/commodity.h"

#include <qDebug>

class RfidCardReadInfo
{
public:
    explicit RfidCardReadInfo();
    explicit RfidCardReadInfo(QString cardData, const QString &cardID, const QDateTime &dateTime);
    explicit RfidCardReadInfo(const QString &cardID, const QDateTime &dateTime, const Commodity &commodityValue);
    explicit RfidCardReadInfo(const RfidCardReadInfo &rfidCardReadInfo);
    virtual ~RfidCardReadInfo();

    QString getCardID() const;
    void setCardID(const QString &value);

    QDateTime getDateTime() const;
    void setDateTime(const QDateTime &value);

    Commodity getCommodity() const;
    void setCommodity(const Commodity &value);

    QString toString() const;

    bool operator ==(const RfidCardReadInfo &t) const;
    bool operator < (const RfidCardReadInfo &t) const;

private:
    //卡号
    QString cardID;
    //读卡时间
    QDateTime dateTime;
    //商品
    Commodity commodity;
};

#endif // RFIDCARDREADINFO_H
