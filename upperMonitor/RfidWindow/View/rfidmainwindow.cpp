#include "rfidmainwindow.h"
#include "ui_rfidmainwindow.h"

RfidMainWindow::RfidMainWindow(QWidget *parent):
    ui(new Ui::RfidMainWindow)
{
    ui->setupUi(this);
    qSerialPorts.clear();
    connect(this, SIGNAL(devConnection()), this, SLOT(connectCardReader()));
    connect(this, SIGNAL(devDisConnection()), this, SLOT(disconnectCardReader()));
    //程序启动的时候发送一个扫描端口的信号
    emit devConnection();
}

RfidMainWindow::~RfidMainWindow()
{
    delete ui;

    QMap<QString, RfidOperating *>::iterator cur;
    for(cur = readers.begin(); cur != readers.end(); ++cur)
        delete cur.value();
    readers.clear();

    qSerialPorts.clear();
}

/**
 * @brief 监听USB是否抽插
 * @param eventType
 * @param message
 * @param result
 * @return
 */
bool RfidMainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);
    int msgType = msg->message;
    if(msgType == WM_DEVICECHANGE)
    {
        PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)msg->lParam;
        switch (msg->wParam) {
        case DBT_DEVICEARRIVAL:
            //插USB
            qDebug()<<"插";
            if(DBT_DEVTYP_PORT == lpdb->dbch_devicetype)
            {
                //读卡器只会触发这一个事件
                //PDEV_BROADCAST_DEVICEINTERFACE pDevInf  = (PDEV_BROADCAST_DEVICEINTERFACE)lpdb;
                emit devConnection();
            }
            break;
        case DBT_DEVICEREMOVECOMPLETE:
            //拔USB
            if(DBT_DEVTYP_PORT == lpdb->dbch_devicetype)
            {
                //读卡器只会触发这一个事件
                qDebug()<<"拔";
                emit devDisConnection();
            }
            break;
        }
    }
    return false;
}

void RfidMainWindow::insertComPort(QSerialPortInfo info)
{
    qSerialPorts.append(info.portName());
}

void RfidMainWindow::revomeComPort(QString comPortName)
{
    qSerialPorts.removeOne(comPortName);
    if(readers[comPortName])
        delete readers[comPortName];
    readers[comPortName] = 0;
    readers.remove(comPortName);
}

/**
 * @brief 串口连接响应槽
 */
void RfidMainWindow::connectCardReader()
{
    foreach (QSerialPortInfo info, QSerialPortInfo::availablePorts())
    {
        //如果不包含读卡器串口，则保存到QList里面
        if(!qSerialPorts.contains(info.portName()))
        {
            qDebug()<<"新增串口"<<info.portName();
            qDebug()<<"此串口为读卡器";
            insertComPort(info);
        }
    }
}

/**
 * @brief 删除连接响应槽
 */
void RfidMainWindow::disconnectCardReader()
{
    QList <QString> portNames;
    foreach (QSerialPortInfo info, QSerialPortInfo::availablePorts())
        portNames.append(info.portName());

    foreach (QString comPortName, qSerialPorts)
    {
        //获取到具体拔了哪根串口
        if(!portNames.contains(comPortName))
        {
            qDebug()<<"删除串口"<<comPortName;
            revomeComPort(comPortName);
        }
    }
}
