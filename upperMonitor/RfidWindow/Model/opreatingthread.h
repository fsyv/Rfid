#ifndef OPREATINGTHREAD_H
#define OPREATINGTHREAD_H

#include <QThread>

QT_BEGIN_NAMESPACE
class RfidOpreatingMachine;
QT_END_NAMESPACE

class OpreatingThread: public QThread
{
    Q_OBJECT
public:
    OpreatingThread(QString comName);
    ~OpreatingThread();
    void run();
    void readInfo();

    void setIsRun(bool value);

private:
    RfidOpreatingMachine *machine;

    bool isRun;
};

#endif // OPREATINGTHREAD_H
