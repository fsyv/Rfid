#include "qconnectionthread.h"

QConnectionThread::QConnectionThread(QObject *parent)
    :QThread(parent)
{

}

void QConnectionThread::run()
{
    while(true)
    {
        usleep(1);
        emit readMessage("收到消息");
    }

}
