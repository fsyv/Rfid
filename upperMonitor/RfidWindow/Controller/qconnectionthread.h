#ifndef QCONNECTIONTHREAD_H
#define QCONNECTIONTHREAD_H

#include <QThread>
#include <QTextCodec>
#include <QByteArray>
#include <QTcpSocket>
#include <QUrl>
#include <QEventLoop>
#include <QDebug>

class QConnectionThread : public QThread
{
    Q_OBJECT
public:
    explicit QConnectionThread();
    ~QConnectionThread();
    void run();

private:
    QTcpSocket *clientTcpSocket;

private slots:
    void readMessage();
    void displayError(QAbstractSocket::SocketError);

};

#endif // QCONNECTIONTHREAD_H
