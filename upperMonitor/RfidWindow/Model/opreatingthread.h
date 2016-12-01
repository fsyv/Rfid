#ifndef OPREATINGTHREAD_H
#define OPREATINGTHREAD_H

#include <QThread>

QT_BEGIN_NAMESPACE
class RfidOpreatingMachine;
class RfidCardReadInfo;
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

signals:
    void sendCardMessage(const RfidCardReadInfo &);

private:
    RfidOpreatingMachine *machine;

    QString preCardID;
    QString currentCardID;

    bool isRun;
};

#endif // OPREATINGTHREAD_H
