#include "connectionservice.h"

ConnectionService::ConnectionService(QString ip, int port, QObject *parent):
    QObject(parent)
{
    this->httpServerUrl = 0;
    manager = 0;
    setServerIpAddress(ip, port);

    QConnectionThread *thread = new QConnectionThread();
    connect(thread, SIGNAL(readMessage(QString), this, SLOT(readMessage(QString)));

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
    httpServerUrl->setScheme("http");
    httpServerUrl->setHost(ip);
    httpServerUrl->setPort(port);

    if(manager)
    {
        disconnect(manager, SIGNAL(finished(QNetworkReply*)),
                   this, SLOT(replyFinished(QNetworkReply*)));
        delete manager;
        manager = 0;
    }
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}

/**
 * @brief get请求
 * @param path 服务器路径
 */
void ConnectionService::get(const QString path)
{
    QUrl serverUrl(*httpServerUrl);
    serverUrl.setPath(path);
    QNetworkRequest request;
    request.setUrl(serverUrl);
    qDebug() << serverUrl.url();
    waitForFinish(manager->get(request));
}


void ConnectionService::post()
{

}

void ConnectionService::replyFinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString replyString = codec->toUnicode(reply->readAll());
    qDebug()<<replyString;
    reply->deleteLater();
}

void ConnectionService::readMessage(QString message)
{
    qDebug() << message;
}

//等待事件get事件完成
//没有这个循环等待会出现无法收到回复的消息，先保留这个问题
void ConnectionService::waitForFinish(QNetworkReply *reply)
{
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
}
