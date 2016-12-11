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
            }
        }
        ui->EmployeeInformation->selectRow(rows);
        ui->NumText->clear();
        ui->PassText->clear();

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
    }

    //删除
    if(ui->DelRadioButton->isChecked())
    {
        bool focus = ui->EmployeeInformation->isItemSelected(ui->EmployeeInformation->currentItem());
        if(focus)
            ui->EmployeeInformation->removeRow(ui->EmployeeInformation->currentItem()->row());
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
