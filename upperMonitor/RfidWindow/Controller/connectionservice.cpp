#include "connectionservice.h"

#include "configureinfo.h"

ConnectionService::ConnectionService(QObject *parent):
    QObject(parent)
{
    clientTcpSocket = new QTcpSocket(this);

    QUrl serverUrl = ConfigureInfo::getSocketServer();

    connect(clientTcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(clientTcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));

    clientTcpSocket->connectToHost(serverUrl.host(), serverUrl.port());

    //    QByteArray byteArray("{\"cardID\":\"7b0362bb\",\"data\":\"\xE6\xA3\x8D\",\"time\":\"\xE5\x91\xA8\xE4\xB8\x80 \xE5\x8D\x81\xE4\xBA\x8C\xE6\x9C\x88 5 22:04:19 2016\"}");

    //    clientTcpSocket->write(byteArray);
}

ConnectionService::~ConnectionService()
{
    clientTcpSocket->disconnectFromHost();
    clientTcpSocket->close();


    if(clientTcpSocket)
        delete clientTcpSocket;
    clientTcpSocket = 0;
}

void ConnectionService::sendMessage(QByteArray byteArray)
{
    qDebug() << "发送消息：";

    byteArray.append("\r\n", strlen("\r\n"));
    qDebug()<< byteArray;
    clientTcpSocket->write(byteArray);
}

void ConnectionService::readMessage()
{
    qDebug() << "收消息：";

    byteArray.append(clientTcpSocket->readAll());

    if(byteArray.at(byteArray.length() - 2) == '\r'&& byteArray.at(byteArray.length() - 1) == '\n')
    {
        QJsonParseError error;
        QJsonDocument parse_doucment = QJsonDocument::fromJson(byteArray, &error);

        qDebug()<<byteArray;

        byteArray.clear();

        qDebug() << error.errorString();

        QJsonObject obj = parse_doucment.object();

        if(obj.contains("MessageType"))
        {
            QJsonValue version_value = obj["MessageType"];
            QString str = version_value.toString();
            if(str == "Query")
            {
                //查询结果
                qDebug() << "收到查询结果";
                emit sendQueryResult(obj);
            }
            else if(str == "InGoods")
            {
                //入库结果
                emit sendInResult(obj);
            }
            else if(str == "OutGoods")
            {
                //出库结果
                emit sendOutResult(obj);
            }
            else if(str == "Login")
            {
                //登录结果
                emit sendLoginResult(obj);
            }
            else if(str == "UserAdd")
            {
                //用户增加结果
                emit sendQueryResult(obj);
            }
            else if(str == "UserDel")
            {
                //用户删除结果
                emit sendQueryResult(obj);
            }
        }
    }


}

void ConnectionService::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<clientTcpSocket->errorString();

    clientTcpSocket->close();
}
