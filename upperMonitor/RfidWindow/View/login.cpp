#include "login.h"
#include "ui_login.h"
#include "View/widgeterror.h"
#include "View/rfidmainwindow.h"
#include "View/administratormainwindow.h"
#include <QMessageBox>
#include <qDebug>

#include "Controller/connectionservice.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    rfidMainWindow = 0;

    service = new ConnectionService(this);
    connect(service, SIGNAL(sendLoginResult(QJsonObject)), this, SLOT(receiverLoginRuselt(QJsonObject)));
}

Login::~Login()
{
    if(service)
        delete service;

    service = 0;

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

void Login::checkUserNameAndPassIsRight()
{

}

void Login::adminWidget()
{
    administratorMainwindow = new AdministratorMainwindow();

    if(!administratorMainwindow)
    {
        throw new WidgetError("内存不足", WidgetError::MemoryError);
    }


    connect(administratorMainwindow, SIGNAL(sendMessage(QByteArray)), service, SLOT(sendMessage(QByteArray)));
    connect(administratorMainwindow, SIGNAL(exitWidget()), this, SLOT(employeeWidgetLogout()));

    connect(service, SIGNAL(sendQueryResult(QJsonObject)), administratorMainwindow, SLOT(receiveMessage(QJsonObject)));

    sendMessageForUsersInfo();

    administratorMainwindow->show();
}

void Login::employeeWidget()
{
    rfidMainWindow = new RfidMainWindow();

    if(!rfidMainWindow)
    {
        throw new WidgetError("内存不足", WidgetError::MemoryError);
    }

    connect(rfidMainWindow, SIGNAL(sendMessage(QByteArray)), service, SLOT(sendMessage(QByteArray)));
    connect(rfidMainWindow, SIGNAL(exitWidget()), this, SLOT(employeeWidgetLogout()));

    connect(service, SIGNAL(sendQueryResult(QJsonObject)), rfidMainWindow, SLOT(receiveQueryResult(QJsonObject)));
    connect(service, SIGNAL(sendInResult(QJsonObject)), rfidMainWindow, SLOT(receiveInResult(QJsonObject)));
    connect(service, SIGNAL(sendOutResult(QJsonObject)), rfidMainWindow, SLOT(receiveOutResult(QJsonObject)));

    rfidMainWindow->setOperatorName(userName);

    rfidMainWindow->show();

}

void Login::sendMessageForUsersInfo()
{
    QJsonObject json;
    json.insert("MessageType", "Query");
    //入库查询
    json.insert("QueryType", "Users");

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArrayFromJson = document.toJson(QJsonDocument::Compact);

    service->sendMessage(byteArrayFromJson);
}

void Login::on_LoginPushButton_clicked()
{

    getUserNameAndPassFromWidget();

    if(checkInputIsEmpty())
    {
        errorMessage("账号密码不能为空!");
        return;
    }

//    QJsonObject json;
//    json.insert("MessageType", "Login");
//    json.insert("UserName", userName);
//    json.insert("UserPass", userPass);

//    QJsonDocument document;
//    document.setObject(json);
//    QByteArray byteArrayFromJson = document.toJson(QJsonDocument::Compact);

//    qDebug() << "登录";
//    qDebug() << byteArrayFromJson;

//    service->sendMessage(byteArrayFromJson);

    //登录成功
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

void Login::adminWidgetLogout()
{
    delete administratorMainwindow;
    administratorMainwindow = 0;
    this->show();
}

void Login::on_exitPushButton_clicked()
{
    close();
}

void Login::receiverLoginRuselt(QJsonObject obj)
{
    if(obj.contains("Ruselt"))
    {
        QString str = obj.take("Ruselt").toString();
        if(QString("TRUE") == str)
        {
            //登录成功
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
        else if(QString("FLASE") == str)
        {
            //登录失败
            QMessageBox::critical(0, "错误", "账号密码错误", QMessageBox::Ok);
        }
    }

}
