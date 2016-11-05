#ifndef RFIDMAINWINDOW_H
#define RFIDMAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <qDebug>
#include <QList>

//USB抽插事件用的
#include <dbt.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "rfidoperating.h"

namespace Ui {
class RfidMainWindow;
}

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
    //USE抽插事件
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    //添加端口到字典
    void insertComPort(QSerialPortInfo info);
    //移除字典中的端口
    void revomeComPort(QString comPortName);
};

#endif // RFIDMAINWINDOW_H
