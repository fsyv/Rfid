#include "queryresult.h"
#include "ui_queryresult.h"

QueryResult::QueryResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryResult)
{
    ui->setupUi(this);
}

QueryResult::QueryResult(QByteArray byteArray, QWidget *parent):
    QDialog(parent),
    ui(new Ui::QueryResult)
{
    ui->setupUi(this);

}

QueryResult::~QueryResult()
{
    delete ui;
}
