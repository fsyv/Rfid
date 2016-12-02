#include "rfidmainwindow.h"
#include "ui_rfidmainwindow.h"
#include "Controller/connectionservice.h"

#include "Model/opreatingthread.h"
#include "Model/rfidcardreadinfo.h"
#include "Controller/configureinfo.h"

RfidMainWindow::RfidMainWindow(QWidget *parent):
    ui(new Ui::RfidMainWindow),
    currentWorkType(NO_WORK_TYPE)
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
    //这两个在不同的线程
    connect(machine, SIGNAL(sendCardMessage(RfidCardReadInfo)), this, SLOT(updateTextEdit(RfidCardReadInfo)), Qt::QueuedConnection);
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
            if(info.description() == ConfigureInfo::getRfidDescription())
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

void RfidMainWindow::updateTextEdit(const RfidCardReadInfo &rfidCardReadInfo)
{
    QString workInfo("");

    workInfo += rfidCardReadInfo.getDate().toString() + "\n";

    switch(currentWorkType){
    case IN_OF_The_LIBRARY:
        workInfo += "出库";
        break;
    case OUT_OF_The_LIBRARY:
        workInfo += "入库";
        break;
    default:
        break;
    }

    workInfo += "货物";
    workInfo += rfidCardReadInfo.getData() + "\n";

    qDebug() << workInfo;

    ui->textEdit->append(workInfo);
    //自动显示到文本末尾
    QTextCursor cursor =  ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(cursor);
}


void RfidMainWindow::on_enterRadioButton_clicked()
{
    currentWorkType = IN_OF_The_LIBRARY;
}

void RfidMainWindow::on_outRadioButton_clicked()
{
    currentWorkType = OUT_OF_The_LIBRARY;
}

void RfidMainWindow::on_logoutAction_triggered()
{

}
