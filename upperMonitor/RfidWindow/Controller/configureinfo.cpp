#include "configureinfo.h"

ConfigureInfo* ConfigureInfo::pInstance = 0;
QMutex ConfigureInfo::qMutex;

ConfigureInfo *ConfigureInfo::getInstance()
{

    if(pInstance)
        return pInstance;
    else
    {
        qMutex.lock();
        pInstance = new ConfigureInfo();
        qMutex.unlock();
        return pInstance;
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

