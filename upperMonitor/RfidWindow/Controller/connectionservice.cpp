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
    if(clientTcpSocket->isOpen())
        clientTcpSocket->close();

    if(clientTcpSocket)
        delete clientTcpSocket;
    clientTcpSocket = 0;
}

void ConnectionService::sendMessage(QByteArray byteArray)
{
    qDebug()<< byteArray;
    clientTcpSocket->write(byteArray);
}

void ConnectionService::readMessage()
{
    qDebug() << clientTcpSocket->readAll();
}

void ConnectionService::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<clientTcpSocket->errorString();
    if(clientTcpSocket->isOpen())
        clientTcpSocket->close();
}
