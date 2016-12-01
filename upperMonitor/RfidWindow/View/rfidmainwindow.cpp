#include "rfidmainwindow.h"
#include "ui_rfidmainwindow.h"
#include "Controller/connectionservice.h"

#include "Model/opreatingthread.h"

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

    QMap<QString, OpreatingThread *>::iterator cur;
    for(cur = readers.begin(); cur != readers.end(); ++cur)
    {
        cur.value()->setIsRun(false);
        cur.value()->wait();
        //cur.value()->moveToThread(QThread::currentThread());
        delete cur.value();
    }

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

void RfidMainWindow::closeEvent(QCloseEvent *e)
{
    if(QMessageBox::Yes == QMessageBox::question(NULL, \
                                                 "提示", \
                                                 "是否关闭?", \
                                                 QMessageBox::Yes|QMessageBox::No))
    {
        logout();
        e->accept();
    }
    else
        e->ignore();
}

void RfidMainWindow::insertComPort(QSerialPortInfo info)
{
    qSerialPorts.append(info.portName());
    OpreatingThread *machine = new OpreatingThread(info.portName());
    readers.insert(info.portName(), machine);

    machine->start();
}

void RfidMainWindow::revomeComPort(QString comPortName)
{
    qSerialPorts.removeOne(comPortName);
    if(readers[comPortName])
    {
        readers[comPortName]->setIsRun(false);
        readers[comPortName]->wait();
//        readers[comPortName]->quit();
        delete readers[comPortName];
    }
    readers[comPortName] = 0;
    readers.remove(comPortName);
}

/**
 * @brief 注销登录
 */
void RfidMainWindow::logout()
{
    emit exitWidget();
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
            if(info.description() == QString("Silicon Labs CP210x USB to UART Bridge"))
            {
                qDebug()<<"此串口为读卡器";
                insertComPort(info);
            }
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


void RfidMainWindow::on_enterRadioButton_clicked()
{

}

void RfidMainWindow::on_outRadioButton_clicked()
{

}

void RfidMainWindow::on_logoutAction_triggered()
{

}
