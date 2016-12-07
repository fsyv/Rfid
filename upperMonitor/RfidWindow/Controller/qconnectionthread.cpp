#include "qconnectionthread.h"

#include "configureinfo.h"

QConnectionThread::QConnectionThread()
    :QThread()
{
    clientTcpSocket = new QTcpSocket(this);

    QUrl serverUrl = ConfigureInfo::getSocketServer();

    clientTcpSocket->connectToHost(serverUrl.host(), serverUrl.port());

    connect(clientTcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(clientTcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));
}

QConnectionThread::~QConnectionThread()
{
    if(clientTcpSocket->isOpen())
        clientTcpSocket->close();

    if(clientTcpSocket)
        delete clientTcpSocket;

    clientTcpSocket = 0;

}

void QConnectionThread::run()
{
    qDebug() << "socketClientRun";
    exec();
}

void QConnectionThread::readMessage()
{
    qDebug() << clientTcpSocket->readAll();
}

void QConnectionThread::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<clientTcpSocket->errorString();
    if(clientTcpSocket->isOpen())
        clientTcpSocket->close();
}
