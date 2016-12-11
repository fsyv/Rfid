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
        QString queryType = json["QueryType"].toString();

        if(queryType == QString("Obligation"))
        {
            //库存查询结果
            qDebug() << "库存查询结果";
            obligationResult();
        }
        else if(queryType == QString("InGoods"))
        {
            //入库查询结果
            qDebug() << "入库查询结果";
            inGoodsResult();
        }
        else if(queryType == QString("OutGoods"))
        {
            //出库查询结果
            qDebug() << "出库查询结果";
            outGoodsResult();
        }
        else if(queryType == QString("Supplier"))
        {
            //供应商查询结果
            qDebug() << "供应商查询结果";
            supplierResult();
        }
    }
}

void QueryResult::obligationResult()
{
    setWindowTitle("库存查询");
    if(json.contains("Quantity"))
    {
        int count = json["Quantity"].toInt();
        for(int i = 0; i < count; ++i)
        {
            QString str("");

            if(json.contains(QString("Commint" + QString::number(i))))
            {
                qDebug() << QString("Commint" + QString::number(i));

                QJsonObject obj = json[QString("Commint" + QString::number(i))].toObject();
                if(obj.contains("depotNo"))
                    str += QString("仓库编号: ") + obj["depotNo"].toString();

                if(obj.contains("goodsName"))
                    str += QString("名字: ") + obj["goodsName"].toString();

                if(obj.contains("goodsSum"))
                    str += QString("库存: ") + QString::number(obj["goodsSum"].toInt());

                if(obj.contains("goodsPrice"))
                    str += QString("价格: ") + QString::number(obj["goodsPrice"].toInt());

                if(obj.contains("goodsWeight"))
                    str += QString("重量: ") + QString::number(obj["goodsWeight"].toInt());

                ui->textEdit->append(str);
            }
        }
    }
}

void QueryResult::inGoodsResult()
{
    setWindowTitle("入库查询");
    if(json.contains("Quantity"))
    {
        int count = json["Quantity"].toInt();
        for(int i = 0; i < count; ++i)
        {
            QString str("");
            if(json.contains(QString("Commint" + QString::number(i))))
            {
                QJsonObject obj = json[QString("Commint" + QString::number(i))].toObject();


                if(obj.contains("username"))
                    str += QString("操作员: ") + obj["username"].toString();

                if(obj.contains("inOrOutNo"))
                    str += QString("入库单号") + obj["inOrOutNo"].toString();

                if(obj.contains("inOrOutGoods"))
                {
                    QJsonArray jsonArray = obj["inOrOutGoods"].toArray();

                    for(int i = 0; i < jsonArray.count(); ++i)
                    {
                        QJsonObject arrayObj = jsonArray.at(i).toObject();

                        str += "\n\t";

                        if(arrayObj.contains("goodsName"))
                            str += QString("商品名字: ") + arrayObj["goodsName"].toString();

                        if(arrayObj.contains("goodsNum"))
                            str += QString("商品数量: ") + QString::number(arrayObj["goodsNum"].toInt());

                    }
                }

                ui->textEdit->append(str);
            }
        }
    }
}

void QueryResult::outGoodsResult()
{
    setWindowTitle("出库查询");
    if(json.contains("Quantity"))
    {
        int count = json["Quantity"].toInt();
        for(int i = 0; i < count; ++i)
        {
            QString str("");
            if(json.contains(QString("Commint" + QString::number(i))))
            {
                QJsonObject obj = json[QString("Commint" + QString::number(i))].toObject();


                if(obj.contains("username"))
                    str += QString("操作员: ") + obj["username"].toString();

                if(obj.contains("inOrOutNo"))
                    str += QString("出库单号") + obj["inOrOutNo"].toString();

                if(obj.contains("inOrOutGoods"))
                {
                    QJsonArray jsonArray = obj["inOrOutGoods"].toArray();


                    for(int i = 0; i < jsonArray.count(); ++i)
                    {
                        QJsonObject arrayObj = jsonArray.at(i).toObject();

                        str += "\n\t";

                        if(arrayObj.contains("goodsName"))
                            str += QString("商品名字: ") + arrayObj["goodsName"].toString();

                        if(arrayObj.contains("goodsNum"))
                            str += QString("商品数量: ") + QString::number(arrayObj["goodsNum"].toInt());

                    }
                }


                ui->textEdit->append(str);
            }
        }
    }
}

void QueryResult::supplierResult()
{
    setWindowTitle("供应商查询");
    if(json.contains("Quantity"))
    {
        int count = json["Quantity"].toInt();
        for(int i = 0; i < count; ++i)
        {
            QString str("");
            if(json.contains(QString("Commint" + QString::number(i))))
            {
                QJsonObject obj = json[QString("Commint" + QString::number(i))].toObject();

                if(obj.contains("supplierName"))
                    str += QString("供应商名字: ") + obj["supplierName"].toString();

                if(obj.contains("supplierNo"))
                    str += QString("供应商编号: ") + obj["supplierNo"].toString();

                ui->textEdit->append(str);
            }
        }
    }
}
