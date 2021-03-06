#ifndef CONFIGUREINFO_H
#define CONFIGUREINFO_H

#include <QSettings>
#include <QMutex>
#include <QTextCodec>
#include <QUrl>

#include <qDebug>

/**
 * @brief 全局单实例类，配置文件的读取
 */

class ConfigureInfo
{
public:
    static ConfigureInfo* getInstance();
    static QString getRfidDescription();
    static QUrl getSocketServer();

private:
    ConfigureInfo();
    ~ConfigureInfo();
    QSettings *configureSettings;
    static ConfigureInfo* pInstance;
    static QMutex qMutex;

};

#endif // CONFIGUREINFO_H
