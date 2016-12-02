#ifndef RFIDCARDREADINFO_H
#define RFIDCARDREADINFO_H

#include <QString>
#include <QDateTime>

class RfidCardReadInfo
{
public:
    explicit RfidCardReadInfo();
    explicit RfidCardReadInfo(QString data, QString cardID, QDateTime dateTime);
    explicit RfidCardReadInfo(const RfidCardReadInfo &rfidCardReadInfo);
    virtual ~RfidCardReadInfo();

    QDateTime getDateTime() const;

    QString getCardID() const;

    QString getData() const;

private:
    QString data;
    QString cardID;
    QDateTime dateTime;
};

#endif // RFIDCARDREADINFO_H
