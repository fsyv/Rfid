#ifndef CONNECTIONSERVICE_H
#define CONNECTIONSERVICE_H
#include <QObject>
#include <QDebug>
#include <QtNetwork>
#include <QTextCodec>
#include <QNetworkReply>    //回复
#include <QNetworkRequest>  //请求
#include <QNetworkAccessManager>
#include <QUrl>

#include "connectionserviceerror.h"

class ConnectionService:public QObject
{
    Q_OBJECT
public:
    explicit ConnectionService(QString ip, int port);
    ~ConnectionService();
    void setServerIpAddress(QString ip, int port);
    void get(QString path);
    void post();

private:
    QNetworkAccessManager *manager;
    QUrl *httpServerUrl;
private slots:
    void replyFinished(QNetworkReply *reply);
};

#endif // CONNECTIONSERVICE_H
