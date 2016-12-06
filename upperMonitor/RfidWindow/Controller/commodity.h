#ifndef COMMODITY_H
#define COMMODITY_H
#include <QtCore>

/**
 * @brief 商品的对象
 * @anchor fsyv@qq.com
 * @date 2016年11月6日
 * @version 1.0
 */
class Commodity
{
public:
    explicit Commodity(QString ID = "", QString name = "", int weiget = 0, int price = 0,
                       QString supplierID = "", QString supplierName = "");

    Commodity(const Commodity &commodity);


    QString getID() const;
    void setID(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    int getWeiget() const;
    void setWeiget(int value);

    int getPrice() const;
    void setPrice(int value);

    QString getSupplierID() const;
    void setSupplierID(const QString &value);

    QString getSupplierName() const;
    void setSupplierName(const QString &value);

private:
    //商品ID
    QString ID;
    //商品名称
    QString name;
    //商品重量
    int weiget;
    //商品单价
    int price;
    //供应商ID
    QString supplierID;
    //供应商名字
    QString supplierName;
};

#endif // COMMODITY_H
