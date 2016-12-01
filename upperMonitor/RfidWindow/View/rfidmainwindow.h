#ifndef RFIDMAINWINDOW_H
#define RFIDMAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <qDebug>
#include <QList>
#include <QThreadPool>
#include <QCloseEvent>
#include <QTextCursor>
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
class OpreatingThread;
class RfidCardReadInfo;
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

private slots:
    //连接与断开读卡器
    void connectCardReader();
    void disconnectCardReader();
    //刷新显示框用
    void updateTextEdit(const RfidCardReadInfo &rfidCardReadInfo);

private:
    enum ReadCardWorkType{
        NO_WORK_TYPE = 0,            //没有设置工作状态
        IN_OF_The_LIBRARY , //入库
        OUT_OF_The_LIBRARY     //出库

    };

    Ui::RfidMainWindow *ui;
    //保存端口信息
    QList<QString> qSerialPorts;
    //连接的读卡器设备
    QMap<QString, OpreatingThread *> readers;
    //当前是出库还是入库
    ReadCardWorkType currentWorkType;

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
