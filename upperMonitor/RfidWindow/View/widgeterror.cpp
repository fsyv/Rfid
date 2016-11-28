#include "widgeterror.h"

WidgetError::WidgetError():
    QException()
{

}

WidgetError::WidgetError(const QString &errorString, const WidgetError::ErrorType &errorType):
    QException()
{
    this->errorString = errorString;
    this->errorType = errorType;
}

WidgetError::~WidgetError() throw()
{

}

QString WidgetError::getErrorString() const
{
    return errorString;
}

