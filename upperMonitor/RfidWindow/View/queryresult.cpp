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
    if(json.contains("Count"))
    {
        int count = json.take("Count").toInt();
        for(int i = 0; i < count; ++i)
        {
            QString str("");
            if(json.contains("Commint" + i))
            {
                QJsonObject obj = json.take("Commint" + i).toObject();
                if(obj.contains("supplierName"))
                    str += obj.take("supplierName").toString();

                if(obj.contains("supplierNo"))
                    str += obj.take("supplierNo").toString();

                ui->textEdit->append(str);
            }
        }
    }
}

void QueryResult::inGoodsResult()
{

}

void QueryResult::outGoodsResult()
{

}

void QueryResult::supplierResult()
{

}
