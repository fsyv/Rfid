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
    if(ui->AddRadioButton->isChecked())
    {
        //        for(int i = 0; i < ui->EmployeeInformation->rowCount();i++)
        //      {
        //            ui->EmployeeInformation->setItem(0, 0, new QTableWidgetItem(ui->NumText->text()));
        //            ui->EmployeeInformation->setItem(0, 1, new QTableWidgetItem(ui->PassText->text()));


        int cols = ui->EmployeeInformation->columnCount();
        int rows = ui->EmployeeInformation->rowCount();
        qDebug()<<rows;
        ui->EmployeeInformation->insertRow(rows);
        for(int i = 0;i < cols;i++)
        {
            ui->EmployeeInformation->setItem(rows,0,new QTableWidgetItem(ui->NumText->text()));
            ui->EmployeeInformation->setItem(rows,1,new QTableWidgetItem(ui->PassText->text()));

        }
        ui->EmployeeInformation->selectRow(rows);
        ui->NumText->clear();
        ui->PassText->clear();
        //       }
    }
    else if(ui->FindRadioButton->isChecked())
    {
        QMessageBox::information(NULL,"查询结果","该员工编号为：" + ui->NumText->text() + "\n该员工密码为：" ,"返回");
    }
    else if(ui->DelRadioButton->isChecked())
    {
    //   int i = ui->EmployeeInformation->setCurrentCell(row,QItemSelectionModel::);
     int i =ui->EmployeeInformation->currentRow();
      if(i != -1)
          ui->EmployeeInformation->removeRow(i);

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
