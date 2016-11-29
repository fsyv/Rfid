#include "login.h"
#include "ui_login.h"
#include "View/widgeterror.h"
#include "View/rfidmainwindow.h"
#include <QMessageBox>
#include <qDebug>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    rfidMainWindow = 0;
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
    return true;
}

void Login::adminWidget()
{
    qDebug()<<"我是管理员";
}

void Login::employeeWidget()
{
    rfidMainWindow = new RfidMainWindow();

    if(!rfidMainWindow)
    {
        throw new WidgetError("内存不足", WidgetError::MemoryError);
    }

    connect(rfidMainWindow, SIGNAL(exitWidget()), this, SLOT(employeeWidgetLogout()));
    rfidMainWindow->show();

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
        adminWidget();
        break;
    case '1':
        //员工
        employeeWidget();
        break;
    default:
        errorMessage("账号错误");
        return;
    }
    this->hide();
}

void Login::employeeWidgetLogout()
{
    delete rfidMainWindow;
    rfidMainWindow = 0;
    this->show();
}
