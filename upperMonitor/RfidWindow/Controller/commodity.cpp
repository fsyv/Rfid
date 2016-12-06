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

int Commodity::getInStock() const
{
    return inStock;
}

void Commodity::setInStock(int value)
{
    inStock = value;
}
