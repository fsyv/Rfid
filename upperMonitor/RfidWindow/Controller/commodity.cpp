#include "commodity.h"

Commodity::Commodity(QString ID, QString name, int weiget, int price, QString supplierID, QString supplierName)
{
    setID(ID);

    setName(name);

    setWeiget(weiget);

    setPrice(price);

    setSupplierID(supplierID);

    setSupplierName(supplierName);
}

Commodity::Commodity(const Commodity &commodity)
{
    this->ID = commodity.getID();
    this->name = commodity.getName();
    this->weiget = commodity.getWeiget();
    this->price = commodity.getPrice();
    this->supplierID = commodity.getSupplierID();
    this->supplierName = commodity.getSupplierName();
}

QString Commodity::getID() const
{
    return ID;
}

void Commodity::setID(const QString &value)
{
    ID = value;
}


QString Commodity::getName() const
{
    return name;
}

void Commodity::setName(const QString &value)
{
    name = value;
}

int Commodity::getWeiget() const
{
    return weiget;
}

void Commodity::setWeiget(int value)
{
    weiget = value;
}

int Commodity::getPrice() const
{
    return price;
}

void Commodity::setPrice(int value)
{
    price = value;
}

QString Commodity::getSupplierID() const
{
    return supplierID;
}

void Commodity::setSupplierID(const QString &value)
{
    supplierID = value;
}

QString Commodity::getSupplierName() const
{
    return supplierName;
}

void Commodity::setSupplierName(const QString &value)
{
    supplierName = value;
}

