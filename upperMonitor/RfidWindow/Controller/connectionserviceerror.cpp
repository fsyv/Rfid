#include "connectionserviceerror.h"

ConnectionServiceError::ConnectionServiceError(const QString errorInfo, ConnectionServiceError::ErrorType &errorType, QException *exception)
{
    this->errorInfo = errorInfo;
    this->errorType = errorType;
}
