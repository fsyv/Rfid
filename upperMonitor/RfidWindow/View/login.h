#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>

namespace Ui {
class Login;
}

QT_BEGIN_NAMESPACE
class QMessageBox;
class RfidMainWindow;
class AdministratorMainwindow;
class ConnectionService;
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private:
    void getUserNameAndPassFromWidget();
    void errorMessage(QString errorString);
    bool checkInputIsEmpty();
    void checkUserNameAndPassIsRight();
    //管理员的界面
    void adminWidget();
    //员工的界面
    void employeeWidget();
    //请求所有用户信息
    void sendMessageForUsersInfo();

private slots:
    void on_LoginPushButton_clicked();
    void employeeWidgetLogout();
    void adminWidgetLogout();

    void on_exitPushButton_clicked();
    //登录结果
    void receiverLoginRuselt(QJsonObject obj);

private:
    Ui::Login *ui;
    QString userName;
    QString userPass;
    RfidMainWindow *rfidMainWindow;
    AdministratorMainwindow *administratorMainwindow;
    //链接服务端
    ConnectionService *service;
};

#endif // LOGIN_H
