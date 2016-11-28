#include "qconnectionthread.h"

QConnectionThread::QConnectionThread()
    :QThread()
{

}

void QConnectionThread::run()
{
    while(true)
    {
        sleep(1);
        emit readMessage("收到消息");
    }

}
