#ifndef QCONNECTIONTHREAD_H
#define QCONNECTIONTHREAD_H

#include <QThread>
#include <QDebug>

class QConnectionThread : public QThread
{
    Q_OBJECT
public:
    explicit QConnectionThread();
    void run();

signals:
    void readMessage(QString);

};

#endif // QCONNECTIONTHREAD_H
