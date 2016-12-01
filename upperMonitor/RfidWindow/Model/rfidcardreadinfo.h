#ifndef RFIDCARDREADINFO_H
#define RFIDCARDREADINFO_H

#include <QString>
#include <QDate>

class RfidCardReadInfo
{
public:
    RfidCardReadInfo(QString data, QString cardID, QDate date);

    QDate getDate() const;

    QString getCardID() const;

    QString getData() const;

private:
    QString data;
    QString cardID;
    QDate date;
};

#endif // RFIDCARDREADINFO_H
