#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QCloseEvent>

namespace Ui {
class AdministratorMainwindow;
}

class AdministratorMainwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorMainwindow(QWidget *parent = 0);
    ~AdministratorMainwindow();

protected:
    //界面关闭事件
    void closeEvent(QCloseEvent *e);

private:
    //刷新界面显示框
    void updateWidget(QJsonObject json);

private slots:
    void on_Determine_clicked();

    void on_EmployeeInformation_activated(const QModelIndex &index);

    void on_Cancel_clicked();

signals:
    //发送消息
    void sendMessage(QByteArray);
    //退出
    void exitWidget();

public slots:
    //收到消息
    void receiveMessage(QJsonObject obj);

private:
    Ui::AdministratorMainwindow *ui;

};

#endif // MAINWINDOW_H
