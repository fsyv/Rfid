#ifndef RFIDMAINWINDOW_H
#define RFIDMAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <qDebug>
#include <QList>
#include <QThreadPool>
#include <QCloseEvent>
#include <QMessageBox>

//USB抽插事件用的
#include <dbt.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "Model/rfidoperating.h"
#include "Controller/connectionservice.h"

namespace Ui {
class RfidMainWindow;
}

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

class RfidMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RfidMainWindow(QWidget *parent = 0);
    ~RfidMainWindow();

signals:
    //use设备连接与断开的信号
    void devConnection();
    void devDisConnection();
    //退出
    void exitWidget();

public slots:
    void connectCardReader();
    void disconnectCardReader();

private:
    Ui::RfidMainWindow *ui;
    //保存端口信息
    QList<QString> qSerialPorts;
    //连接的读卡器设备
    QMap<QString, RfidOperating *> readers;

protected:
    //USB抽插事件
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    //界面关闭事件
    void closeEvent(QCloseEvent *e);
    //添加端口到字典
    void insertComPort(QSerialPortInfo info);
    //移除字典中的端口
    void revomeComPort(QString comPortName);
    //注销
    void logout();
private slots:
    void on_enterRadioButton_clicked();
    void on_outRadioButton_clicked();
    void on_logoutAction_triggered();
};

#endif // RFIDMAINWINDOW_H
