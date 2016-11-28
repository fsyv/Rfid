#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>


namespace Ui {
class Login;
}

QT_BEGIN_NAMESPACE
class QMessageBox;
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
    bool checkUserNameAndPassIsRight();
    //界面的回调函数
    typedef void(*pWidgetCallBack)();
    //管理员的界面
    void adminWidget();
    //员工的界面
    void employeeWidget();

private slots:
    void on_LoginPushButton_clicked();

private:
    Ui::Login *ui;
    QString userName;
    QString userPass;
    pWidgetCallBack currenWidget;
};

#endif // LOGIN_H
