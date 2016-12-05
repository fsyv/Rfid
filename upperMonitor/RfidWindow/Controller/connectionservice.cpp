#include "connectionservice.h"

#include "configureinfo.h"

ConnectionService::ConnectionService(QObject *parent):
    QObject(parent)
{
    clientTcpSocket = new QTcpSocket(this);

    QUrl serverUrl = ConfigureInfo::getSocketServer();

    clientTcpSocket->connectToHost(serverUrl.host(), serverUrl.port());

    connect(clientTcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(clientTcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));
}

ConnectionService::~ConnectionService()
{
    
}

void ConnectionService::readMessage()
{
    qDebug() << clientTcpSocket->readAll();
}

void ConnectionService::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<clientTcpSocket->errorString();
    clientTcpSocket->close();
}
