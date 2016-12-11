#include "rfidmainwindow.h"
#include "ui_rfidmainwindow.h"
#include "Controller/connectionservice.h"

#include "Model/opreatingthread.h"
#include "Controller/configureinfo.h"

Q_DECLARE_METATYPE(RfidCardReadInfo)

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

    int id=qRegisterMetaType<RfidCardReadInfo>("");
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

QString RfidMainWindow::getRandString()
{
    int max = 8;
    QString tmp = "0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
    QString str("");
    str += QString::number(QDate::currentDate().year());
    str += QString::number(QDate::currentDate().month());

    qDebug() << str;

    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);
    for(int i = 0; i < max; ++i)
        str += tmp.at(qrand() % tmp.length());

    return str;
}

void RfidMainWindow::toJson()
{
    jsonObject->insert("Quantity", currentRecInfo.count());

    int index = 0;
    QMap<RfidCardReadInfo, int>::iterator cur;
    for(cur = currentRecInfo.begin(); cur != currentRecInfo.end(); ++cur)
    {
        QJsonObject commodityObject;

        commodityObject.insert("Count", cur.value());
        commodityObject.insert("ID", cur.key().getCommodity().getID());
        commodityObject.insert("Name", cur.key().getCommodity().getName());
        commodityObject.insert("Price", cur.key().getCommodity().getPrice());
        commodityObject.insert("Weiget", cur.key().getCommodity().getWeiget());
        commodityObject.insert("SupplierID", cur.key().getCommodity().getSupplierID());
        commodityObject.insert("SupplierName", cur.key().getCommodity().getSupplierName());

        jsonObject->insert("Commodity" + QString::number(index++), commodityObject);

        qDebug() << "commodityObject" <<commodityObject;
    }
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
    switch(currentWorkType){
    case IN_OF_The_LIBRARY:
        workInfo += "入库";
        break;
    case OUT_OF_The_LIBRARY:
        workInfo += "出库";
        break;
    case NO_WORK_TYPE:
        QMessageBox::critical(NULL, \
                              "提示", \
                              "请先设置入库还是出库！！！", \
                              QMessageBox::Ok);
        return;
    default:
        break;
    }

    QString info = rfidCardReadInfo.toString();

    qDebug() << info;

    if(currentRecInfo.keys().contains(rfidCardReadInfo))
        //currentRecInfo[rfidCardReadInfo] = ;
    {
        qDebug() << currentRecInfo.value(rfidCardReadInfo);
        currentRecInfo.insert(rfidCardReadInfo, currentRecInfo.value(rfidCardReadInfo) + 1);
    }
    else
    {
        qDebug() << "新的商品~~~";
        currentRecInfo.insert(rfidCardReadInfo, 1);
    }


    ui->textEdit->append(info);
    //自动显示到文本末尾
    QTextCursor cursor =  ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(cursor);
}

void RfidMainWindow::receiveQueryResult(QJsonObject obj)
{
    qDebug()<< "有查询结果消息";
    if(obj.contains("QueryType"))
    {
        QString str = obj.take("QueryType").toString();
        if(str != QString("Users"))
        {
            QueryResult *queryResult = new QueryResult(obj);
            queryResult->show();
        }
    }
}

void RfidMainWindow::receiveInResult(QJsonObject obj)
{
    if(obj.contains("Result"))
    {
        QString str = obj.take("Result").toString();
        if(str == QString("true"))
            QMessageBox::information(NULL, "提示", "入库成功", QMessageBox::Ok);
        else if(str == QString("false"))
            QMessageBox::information(NULL, "提示", "入库失败", QMessageBox::Ok);
    }
}

void RfidMainWindow::receiveOutResult(QJsonObject obj)
{
    if(obj.contains("Result"))
    {
        QString str = obj.take("Result").toString();
        if(str == QString("true"))
            QMessageBox::information(NULL, "提示", "出库成功", QMessageBox::Ok);
        else if(str == QString("false"))
            QMessageBox::information(NULL, "提示", "出库失败", QMessageBox::Ok);
    }
}

QString RfidMainWindow::getOperatorName() const
{
    return operatorName;
}

void RfidMainWindow::setOperatorName(const QString &value)
{
    operatorName = value;
}

void RfidMainWindow::on_logoutAction_triggered()
{

}

void RfidMainWindow::on_enterPushButton_clicked(bool checked)
{
    if(checked)
    {
        currentWorkType = IN_OF_The_LIBRARY;
        ui->enterPushButton->setText("停止入库");
        ui->outPushButton->setDisabled(true);
        ui->textEdit->clear();
        ui->textEdit->setText(QString("开始入库时间: ") + QTime::currentTime().toString());

        currentRecInfo.clear();

        jsonObject = new QJsonObject();

        jsonObject->insert("MessageType", "InGoods");
        jsonObject->insert("StartTime", QTime::currentTime().toString());
        jsonObject->insert("OperatorName", operatorName);
        //批次号
        jsonObject->insert("BatchNumber", getRandString());
    }
    else
    {
        currentWorkType = NO_WORK_TYPE;
        ui->enterPushButton->setText("入  库");
        ui->outPushButton->setDisabled(false);
        ui->textEdit->append(QString("停止入库时间: ") + QTime::currentTime().toString());

        jsonObject->insert("EndTime", QTime::currentTime().toString());

        toJson();

        QJsonDocument document;
        document.setObject(*jsonObject);
        QByteArray byteArrayFromJson = document.toJson(QJsonDocument::Compact);

        emit sendMessage(byteArrayFromJson);

        delete jsonObject;
        jsonObject = 0;
    }
}

void RfidMainWindow::on_outPushButton_clicked(bool checked)
{
    if(checked)
    {
        currentWorkType = OUT_OF_The_LIBRARY;
        ui->outPushButton->setText("停止出库");
        ui->enterPushButton->setDisabled(true);
        ui->textEdit->setText(QString("开始出库时间: ") + QTime::currentTime().toString());

        currentRecInfo.clear();

        jsonObject = new QJsonObject();

        jsonObject->insert("MessageType", "OutGoods");
        jsonObject->insert("StartTime", QTime::currentTime().toString());
        jsonObject->insert("OperatorName", operatorName);
        //批次号
        jsonObject->insert("BatchNumber", getRandString());
    }
    else
    {
        currentWorkType = NO_WORK_TYPE;
        ui->outPushButton->setText("出  库");
        ui->enterPushButton->setDisabled(false);
        ui->textEdit->append(QString("停止出库时间: ") + QTime::currentTime().toString());

        jsonObject->insert("EndTime", QTime::currentTime().toString());

        toJson();

        QJsonDocument document;
        document.setObject(*jsonObject);
        QByteArray byteArrayFromJson = document.toJson(QJsonDocument::Compact);

        qDebug() << byteArrayFromJson;

        emit sendMessage(byteArrayFromJson);

        qDebug() << jsonObject;
        delete jsonObject;
        jsonObject = 0;
    }

}

void RfidMainWindow::on_obligationQueryAction_triggered()
{
    QJsonObject json;
    json.insert("MessageType", "Query");
    //库存查询
    json.insert("QueryType", "Obligation");

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArrayFromJson = document.toJson(QJsonDocument::Compact);

    emit sendMessage(byteArrayFromJson);
}

void RfidMainWindow::on_inGoodsQuery_triggered()
{
    QJsonObject json;
    json.insert("MessageType", "Query");
    //入库查询
    json.insert("QueryType", "InGoods");

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArrayFromJson = document.toJson(QJsonDocument::Compact);

    emit sendMessage(byteArrayFromJson);
}

void RfidMainWindow::on_outGoodsQuery_triggered()
{
    QJsonObject json;
    json.insert("MessageType", "Query");
    //出库查询
    json.insert("QueryType", "OutGoods");

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArrayFromJson = document.toJson(QJsonDocument::Compact);

    emit sendMessage(byteArrayFromJson);
}

void RfidMainWindow::on_supplierQuery_triggered()
{
    QJsonObject json;
    json.insert("MessageType", "Query");
    //供应商查询
    json.insert("QueryType", "Supplier");

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArrayFromJson = document.toJson(QJsonDocument::Compact);

    emit sendMessage(byteArrayFromJson);
}
