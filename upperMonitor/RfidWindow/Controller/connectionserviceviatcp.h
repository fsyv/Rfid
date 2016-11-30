#ifndef CONNECTIONSERVICEVIATCP_H
#define CONNECTIONSERVICEVIATCP_H
#include <QtNetwork/QTcpSocket>
#include <QByteArray>

class ConnectionServiceViaTCP
{
public:
    ConnectionServiceViaTCP();

private:
    QTcpSocket *clientTcpSocket;

private slots:
    void readMessage();

};

#endif // CONNECTIONSERVICEVIATCP_H
