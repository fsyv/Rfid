#ifndef CONNECTIONSERVICE_H
#define CONNECTIONSERVICE_H
#include <QObject>
#include <QDebug>
#include <QTextCodec>
#include <QByteArray>
#include <QTcpSocket>
#include <QUrl>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

QT_BEGIN_NAMESPACE
class ConfigureInfo;
QT_END_NAMESPACE

class ConnectionService : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionService(QObject *parent = 0);
    ~ConnectionService();

private:
    QTcpSocket *clientTcpSocket;

signals:
    void sendQueryResult(QJsonObject);
    void sendInResult(QJsonObject);
    void sendOutResult(QJsonObject);
    void sendLoginResult(QJsonObject);

public slots:
    void sendMessage(QByteArray byteArray);

private slots:
    void readMessage();
    void displayError(QAbstractSocket::SocketError);
};

#endif // CONNECTIONSERVICE_H
