#include "configureinfo.h"

ConfigureInfo* ConfigureInfo::pInstance = 0;
QMutex ConfigureInfo::qMutex;

ConfigureInfo *ConfigureInfo::getInstance()
{
    if(pInstance)
        return pInstance;
    else
    {
        //防止多次被实例化
        qMutex.lock();
        if(pInstance)
            return pInstance;
        else
        {
            pInstance = new ConfigureInfo();
            qMutex.unlock();
            return pInstance;
        }
    }
}

QString ConfigureInfo::getRfidDescription()
{
    QSettings *settings = getInstance()->configureSettings;
    //以UTF-8编码解析字符串
    QByteArray byteArray = settings->value("RFIDDESCRIPTION/description").toByteArray();
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString description = codec->toUnicode(byteArray);

    qDebug() << description;

    return description;
}

QUrl ConfigureInfo::getSocketServer()
{
    QSettings *settings = getInstance()->configureSettings;
    //以UTF-8编码解析字符串
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");

    //读取服务器IP
    QByteArray byteArray = settings->value("SOCKETIP/IP").toByteArray();
    QString IP = codec->toUnicode(byteArray);

    //读取服务端端口
    byteArray = settings->value("SOCKETIP/PORT").toByteArray();
    QString port = codec->toUnicode(byteArray);

    QUrl url;
    url.setHost(IP);
    url.setPort(port.toInt());

    qDebug() << url;

    return url;
}

ConfigureInfo::ConfigureInfo()
{
    configureSettings = new QSettings("./system.ini", QSettings::IniFormat);
}

ConfigureInfo::~ConfigureInfo()
{
    if(configureSettings)
        delete configureSettings;
    configureSettings = 0;
}

