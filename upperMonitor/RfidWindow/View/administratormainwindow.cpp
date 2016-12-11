#include "administratormainwindow.h"
#include "ui_administratormainwindow.h"
#include <QTableWidget>
#include <QMessageBox>
#include <QDebug>

AdministratorMainwindow::AdministratorMainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorMainwindow)
{
    ui->setupUi(this);
    //    ui->EmployeeInformation->setEditTriggers(QAbstractItemView::EditTrigger);
}

AdministratorMainwindow::~AdministratorMainwindow()
{
    delete ui;
}

void AdministratorMainwindow::closeEvent(QCloseEvent *e)
{
    if(QMessageBox::Yes == QMessageBox::question(NULL, \
                                                 "提示", \
                                                 "是否关闭?", \
                                                 QMessageBox::Yes|QMessageBox::No)) //提示关闭窗口
    {
        emit exitWidget();
        e->accept();
    }
    else
        e->ignore();
}

void AdministratorMainwindow::updateWidget(QJsonObject json)
{  //更新表格
    if(json.contains("Quantity"))
    {
        int count = json["Quantity"].toInt();
        for(int i = 0; i < count; ++i)
        {
            QString str("");
            if(json.contains(QString("Commint" + QString::number(i))))
            {
                QJsonObject obj = json[QString("Commint" + QString::number(i))].toObject();


                int rows = ui->EmployeeInformation->rowCount();
                ui->EmployeeInformation->insertRow(rows);
                ui->EmployeeInformation->setItem(rows,1,new QTableWidgetItem(ui->PassText->text()));

                if(obj.contains("userNo"))
                    ui->EmployeeInformation->setItem(rows,0,new QTableWidgetItem(obj["userNo"].toString()));

                if(obj.contains("userPwd"))
                    ui->EmployeeInformation->setItem(rows,1,new QTableWidgetItem(obj["userPwd"].toString()));

            }
        }
    }
}

void AdministratorMainwindow::on_Determine_clicked()
{
    QTableWidget *worker = ui->EmployeeInformation;
    //添加
    if(ui->AddRadioButton->isChecked())
    {
        bool exist = false;//初始状态，该员工不存在
        int rows = ui->EmployeeInformation->rowCount();

        qDebug()<<rows;
        for(int i = 0; i < worker->rowCount(); ++i)
        {
            if(ui->NumText->text() == worker->item(i, 0)->text())
            {
                QMessageBox::warning(NULL, "提示",  "已存在该员工", "返回");
                exist = true;//若找到一样的编号，则该员工存在
            }
        }
        if(!exist)//如果未找到一样的编号
        {
            if(ui->NumText->text()==NULL || ui->PassText->text()==NULL)
                QMessageBox::information(NULL,"查询结果","账号或密码均不能空着","返回");
            else
            {
                worker->insertRow(rows);
                ui->EmployeeInformation->setItem(rows,0,new QTableWidgetItem(ui->NumText->text()));
                ui->EmployeeInformation->setItem(rows,1,new QTableWidgetItem(ui->PassText->text()));

                QJsonObject json;
                json.insert("MessageType", "UserAdd");
                json.insert("UserNo", ui->NumText->text());
                json.insert("UserPass", ui->PassText->text());

                QJsonDocument document;
                document.setObject(json);
                QByteArray byteArrayFromJson = document.toJson(QJsonDocument::Compact);

                qDebug() << "新增用户";
                qDebug() << byteArrayFromJson;

                emit sendMessage(byteArrayFromJson);
            }
        }
        ui->EmployeeInformation->selectRow(rows);
        ui->NumText->clear();
        ui->PassText->clear();

        return;
    }

    //查找
    if(ui->FindRadioButton->isChecked())
    {
        bool find = false;
        int row = 0;
        qDebug()<<"number: "<<ui->EmployeeInformation->rowCount();
        for(int i = 0; i < ui->EmployeeInformation->rowCount(); ++i)
        {
            if(ui->NumText->text() == ui->EmployeeInformation->item(i, 0)->text())
            {
                find = true;
                row = i;
                break;
            }
        }
        if(find)
            QMessageBox::information(NULL,"查询结果","该员工编号为：" + ui->EmployeeInformation->item(row, 0)->text() + "\n该员工密码为：" +
                                     ui->EmployeeInformation->item(row, 1)->text() ,"返回");
        else
            QMessageBox::information(NULL,"查询结果","所查找的员工已不在了","返回");

        ui->NumText->clear();
        ui->PassText->clear();
        return;
    }

    //删除
    if(ui->DelRadioButton->isChecked())
    {
        bool focus = ui->EmployeeInformation->isItemSelected(ui->EmployeeInformation->currentItem());
        if(focus)
        {
            QJsonObject json;
            json.insert("MessageType", "UserDel");
            json.insert("UserNo", ui->EmployeeInformation->item(ui->EmployeeInformation->currentItem()->row(), 0)->text());

            QJsonDocument document;
            document.setObject(json);
            QByteArray byteArrayFromJson = document.toJson(QJsonDocument::Compact);

            ui->EmployeeInformation->removeRow(ui->EmployeeInformation->currentItem()->row());

            qDebug() << "删除用户";
            qDebug() << byteArrayFromJson;

            emit sendMessage(byteArrayFromJson);
        }
        return;
    }

}

void AdministratorMainwindow::on_EmployeeInformation_activated(const QModelIndex &index)
{
    ui->EmployeeInformation->setFocusPolicy(Qt::NoFocus);



}

void AdministratorMainwindow::on_Cancel_clicked()
{
    close();
}

void AdministratorMainwindow::receiveMessage(QJsonObject obj)
{
    qDebug()<< "admin收到消息";

    if(obj.contains("MessageType"))
    {
        QString str = obj["MessageType"].toString();
        if(str == QString("UserAdd"))
        {
            //增加用户的结果
            if(obj.contains("Result"))
            {
                str = obj["Result"].toString();
                if(str == QString("true"))
                    QMessageBox::information(NULL, "提示", "增加用户成功", QMessageBox::Ok);
                else if(str == QString("false"))
                    QMessageBox::information(NULL, "提示", "增加用户失败", QMessageBox::Ok);
            }
        }
        else if(str == QString("UserDel"))
        {
            //删除用户的结果
            if(obj.contains("Result"))
            {
                str = obj["Result"].toString();
                if(str == QString("true"))
                    QMessageBox::information(NULL, "提示", "删除用户成功", QMessageBox::Ok);
                else if(str == QString("false"))
                    QMessageBox::information(NULL, "提示", "删除用户失败", QMessageBox::Ok);
            }
        }
        else if(str == QString("Query"))
        {
            //用户查询的结果
            if(obj.contains("QueryType"))
            {
                str = obj["QueryType"].toString();
                if(str == QString("Users"))
                {
                    updateWidget(obj);
                }
            }
        }
    }
}

