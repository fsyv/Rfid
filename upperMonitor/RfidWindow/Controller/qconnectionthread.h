#ifndef QCONNECTIONTHREAD_H
#define QCONNECTIONTHREAD_H

#include <QThread>


class QConnectionThread : public QThread
{
public:
    explicit QConnectionThread(QObject *parent);
    void run();

signals:
    void readMessage(QString);

};

#endif // QCONNECTIONTHREAD_H
