#ifndef RFIDCARDREADINFO_H
#define RFIDCARDREADINFO_H

#include <QString>
#include <QDateTime>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>

#include <qDebug>

class RfidCardReadInfo
{
public:
    explicit RfidCardReadInfo();
    explicit RfidCardReadInfo(QString data, QString cardID, QDateTime dateTime);
    explicit RfidCardReadInfo(const RfidCardReadInfo &rfidCardReadInfo);
    virtual ~RfidCardReadInfo();


    QByteArray getByteArrayFromJson() const;

private:
    void toJson();

private:
    QString data;
    QString cardID;
    QDateTime dateTime;

    QByteArray byteArrayFromJson;
};

#endif // RFIDCARDREADINFO_H
