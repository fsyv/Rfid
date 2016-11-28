#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <qDebug>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::getUserNameAndPassFromWidget()
{
    userName = ui->userNameComboBox->currentText();
    userPass = ui->userPassLineEdit->text();
}

void Login::errorMessage(QString errorString)
{
    QMessageBox::information(NULL, "提示", errorString,QMessageBox::Ok);
}

bool Login::checkInputIsEmpty()
{
    return userName.isEmpty() || userPass.isEmpty();
}

bool Login::checkUserNameAndPassIsRight()
{
    return false;
}

void Login::adminWidget()
{
    qDebug()<<"我是管理员";
}

void Login::employeeWidget()
{
    qDebug()<<"我是员工";
}

void Login::on_LoginPushButton_clicked()
{

    getUserNameAndPassFromWidget();

    if(checkInputIsEmpty())
    {
        errorMessage("账号密码不能为空!");
        return;
    }

    if(!checkUserNameAndPassIsRight())
    {
        errorMessage("账号密码错误!");
        return;
    }

    switch (userName.at(0).unicode()) {
    case '0':
        //管理员
        currenWidget  = (pWidgetCallBack)&(adminWidget);
    case '1':
        //员工
        currenWidget = (pWidgetCallBack)&(employeeWidget);
        break;
    default:
        errorMessage("账号错误");
        return;
    }

    currenWidget();
}
