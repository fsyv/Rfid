#ifndef CONNECTIONSERVICEERROR_H
#define CONNECTIONSERVICEERROR_H
#include<QDebug>
#include <QException>

#include <QtSql/QSqlError>

/**
 * @brief 连接服务器的异常类
 * @anchor fsyv@qq.com
 * @date 2016年11月7日
 * @version 1.0
 */
class ConnectionServiceError:public QException
{
public:
    enum ErrorType {
        NoError,    //没有错误，但是发生了异常情况
        ConnectionError,    //连接服务器失败
        StatementError,
        TransactionError,
        UnknownError
    };
    explicit ConnectionServiceError(const QString errorInfo, ErrorType &errorType, QException *exception = Q_NULLPTR);

private:
    QString errorInfo;
    QSqlError::ErrorType errorType;
    QString errorCode;
};

#endif // CONNECTIONSERVICEERROR_H
