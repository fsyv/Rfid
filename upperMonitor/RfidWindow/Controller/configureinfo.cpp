#include "configureinfo.h"

ConfigureInfo* ConfigureInfo::pInstance = 0;

ConfigureInfo *ConfigureInfo::getInstance()
{

    if(pInstance)
        return pInstance;
    else
    {
        qMutex.lock();
        pInstance = new ConfigureInfo();
        return pInstance;
    }
}

QString ConfigureInfo::getRfidDescription()
{
    QSettings *settings = getInstance()->configureSettings;
    QByteArray byteArray = settings->value("RFIDDESCRIPTION/description").toByteArray();
    QString description;
}

ConfigureInfo::ConfigureInfo()
{
    configureSettings = new QSettings("system.ini", QSettings::IniFormat);
}

ConfigureInfo::~ConfigureInfo()
{
    if(configureSettings)
        delete configureSettings;
    configureSettings = 0;
    qMutex.unlock();
}

