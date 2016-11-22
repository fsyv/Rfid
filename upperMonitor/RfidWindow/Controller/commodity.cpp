#include "commodity.h"

commodity::commodity(QString name, int inStock)
{
    this->name = name;
    this->inStock = inStock;
}

QString commodity::getName() const
{
    return name;
}

void commodity::setName(const QString &value)
{
    name = value;
}

int commodity::getInStock() const
{
    return inStock;
}

void commodity::setInStock(int value)
{
    inStock = value;
}
