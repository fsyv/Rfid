#include "queryresult.h"
#include "ui_queryresult.h"

QueryResult::QueryResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryResult)
{
    ui->setupUi(this);
}

QueryResult::QueryResult(QJsonObject jsonObject, QWidget *parent):
    QDialog(parent),
    ui(new Ui::QueryResult)
{
    ui->setupUi(this);
    json = jsonObject;
    showResultInfo();
}

QueryResult::~QueryResult()
{
    delete ui;
}

void QueryResult::showResultInfo()
{
    if(json.contains("QueryType"))
    {
        QString queryType = json.take("QueryType").toString();

        if(queryType == QString("Obligation"))
        {
            //库存查询结果
            obligationResult();
        }
        else if(queryType == QString("InGoods"))
        {
            //入库查询结果
            inGoodsResult();
        }
        else if(queryType == QString("OutGoods"))
        {
            //出库查询结果
            outGoodsResult();
        }
        else if(queryType == QString("Supplier"))
        {
            //供应商查询结果
            supplierResult();
        }
    }
}

void QueryResult::obligationResult()
{
    if(json.contains("Quantity"))
    {
        int count = json.take("Quantity").toInt();
        for(int i = 0; i < count; ++i)
        {
            QString str("");

            if(json.contains(QString("Commint" + QString::number(i))))
            {
                qDebug() << QString("Commint" + QString::number(i));

                QJsonObject obj = json.take(QString("Commint" + QString::number(i))).toObject();
                if(obj.contains("depotNo"))
                    str += QString("编号: ") + obj.take("depotNo").toString();

                if(obj.contains("goodsName"))
                    str += QString("名字: ") + obj.take("goodsName").toString();

                if(obj.contains("goodsSum"))
                    str += QString("库存: ") + QString::number(obj.take("goodsSum").toInt());

                if(obj.contains("goodsPrice"))
                    str += QString("价格: ") + QString::number(obj.take("goodsPrice").toInt());

                if(obj.contains("goodsWeight"))
                    str += QString("重量: ") + QString::number(obj.take("goodsWeight").toInt());

                ui->textEdit->append(str);
            }
        }
    }
}

void QueryResult::inGoodsResult()
{
    if(json.contains("Quantity"))
    {
        int count = json.take("Quantity").toInt();
        for(int i = 0; i < count; ++i)
        {
            QString str("");
            if(json.contains(QString("Commint" + QString::number(i))))
            {
                QJsonObject obj = json.take(QString("Commint" + QString::number(i))).toObject();


                if(obj.contains("username"))
                    str += QString("操作员: ") + obj.take("username").toString();

                if(obj.contains("inOrOutNo"))
                    str += QString("入库单号") + obj.take("inOrOutNo").toString();

                if(obj.contains("inOrOutGoods"))
                {
                    QJsonArray jsonArray = obj.take("inOrOutGoods").toArray();
                    qDebug() << "json count" <<jsonArray.count();
                    //jsonArray.takeAt();
                }


                ui->textEdit->append(str);
            }
        }
    }
}

void QueryResult::outGoodsResult()
{

}

void QueryResult::supplierResult()
{
    if(json.contains("Quantity"))
    {
        int count = json.take("Quantity").toInt();
        for(int i = 0; i < count; ++i)
        {
            QString str("");
            if(json.contains(QString("Commint" + QString::number(i))))
            {
                QJsonObject obj = json.take(QString("Commint" + QString::number(i))).toObject();

                if(obj.contains("supplierName"))
                    str += QString("供应商名字: ") + obj.take("supplierName").toString();

                if(obj.contains("supplierNo"))
                    str += QString("供应商编号: ") + obj.take("supplierNo").toString();

                ui->textEdit->append(str);
            }
        }
    }
}
