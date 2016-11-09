#ifndef COMMODITY_H
#define COMMODITY_H
#include <QtCore>

/**
 * @brief 商品的信息
 * @anchor fsyv@qq.com
 * @date 2016年11月6日
 * @version 1.0
 */
class commodity
{
public:
    commodity(QString name, int inStock);

private:
    //商品名字
    QString name;
    //商品库存
    int inStock;
};

#endif // COMMODITY_H
