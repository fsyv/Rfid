#ifndef WIDGETERROR_H
#define WIDGETERROR_H
#include <QException>

/**
 * @brief 界面异常类
 */

class WidgetError:
        public QException
{
public:
    enum ErrorType {
        NoError,    //没有错误，但是发生了异常情况
        MemoryError,    //内存错误
        UnknownError
    };
    WidgetError();
    WidgetError(const QString &errorString, const ErrorType &errorType);
    virtual ~WidgetError() throw();

    QString getErrorString() const;

private:
    QString errorString;
    ErrorType errorType;
};

#endif // WIDGETERROR_H
