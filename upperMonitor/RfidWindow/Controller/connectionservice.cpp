#include "connectionservice.h"

ConnectionService::ConnectionService(QString ip, int port):
    QObject()
{
    this->httpServerUrl = 0;
    manager = 0;
    setServerIpAddress(ip, port);
}

ConnectionService::~ConnectionService()
{
    if(manager)
        delete manager;
    manager = 0;

    if(httpServerUrl)
        delete httpServerUrl;
    httpServerUrl = 0;
}

/**
 * @brief 重新设置服务器地址
 * @param httpServerUrl 服务器IP + 端口号
 */
void ConnectionService::setServerIpAddress(QString ip, int port)
{
    if(httpServerUrl)
    {
        delete httpServerUrl;
        httpServerUrl = 0;
    }
    httpServerUrl = new QUrl();
    httpServerUrl->setHost(ip);
    httpServerUrl->setPort(port);

    if(manager)
    {
        disconnect(manager, SIGNAL(finished(QNetworkReply*)),
                            this, SLOT(replyFinished(QNetworkReply*)));
        delete manager;
        manager = 0;
    }
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}

/**
 * @brief get请求
 * @param path 服务器路径
 */
void ConnectionService::get(QString path)
{
    QUrl serverUrl(*httpServerUrl);
    serverUrl.setPath(path);
    manager->get(QNetworkRequest(serverUrl));
}


void ConnectionService::post()
{

}

void ConnectionService::replyFinished(QNetworkReply *)
{

}
