#ifndef CONNECTIONSERVICE_H
#define CONNECTIONSERVICE_H
#include <QObject>
#include <QDebug>
#include <QTextCodec>
#include <QNetworkReply>    //回复
#include <QNetworkRequest>  //请求
#include <QNetworkAccessManager>
#include <QUrl>
#include <QEventLoop>

#include "connectionserviceerror.h"
#include "Controller/qconnectionthread.h"

class ConnectionService : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionService(QString ip, int port, QObject *parent = 0);
    ~ConnectionService();
    void setServerIpAddress(QString ip, int port);
    void get(const QString path);
    void post();

private:
    //等待事件get事件完成
    //没有这个循环等待会出现无法收到回复的消息，先保留这个问题
    void waitForFinish(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QUrl *httpServerUrl;
private slots:
    void replyFinished(QNetworkReply *reply);
    void readMessage(QString message);
};

#endif // CONNECTIONSERVICE_H
