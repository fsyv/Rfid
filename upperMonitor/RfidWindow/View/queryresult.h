#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <QDialog>
#include <QByteArray>
#include <QTextCodec>
#include <QJsonObject>
#include <QJsonArray>
#include <qDebug>

namespace Ui {
class QueryResult;
}

class QueryResult : public QDialog
{
    Q_OBJECT

public:
    explicit QueryResult(QWidget *parent = 0);
    explicit QueryResult(QJsonObject jsonObject, QWidget *parent = 0);
    ~QueryResult();

private:
    void showResultInfo();
    //库存查询结果
    void obligationResult();
    //入库查询结果
    void inGoodsResult();
    //出库查询结果
    void outGoodsResult();
    //供应商查询结果
    void supplierResult();

private:
    Ui::QueryResult *ui;
    QJsonObject json;
};

#endif // QUERYRESULT_H
