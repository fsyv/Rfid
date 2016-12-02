#ifndef CONFIGUREINFO_H
#define CONFIGUREINFO_H

#include <QSettings>
#include <QMutex>
#include <QTextCodec>

/**
 * @brief 全局单实例类，配置文件的读取
 */

class ConfigureInfo
{
public:
    static ConfigureInfo* getInstance();
    static QString getRfidDescription();

private:
    ConfigureInfo();
    ~ConfigureInfo();
    QSettings *configureSettings;
    static ConfigureInfo* pInstance;
    static QMutex qMutex;

};

#endif // CONFIGUREINFO_H
