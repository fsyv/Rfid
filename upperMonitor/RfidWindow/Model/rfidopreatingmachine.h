#ifndef RFIDOPREATINGMACHINE_H
#define RFIDOPREATINGMACHINE_H

#include "rfidoperating.h"
#include <QTimer>

/**
 * @brief 仓库管理系统需要用到的对象
 */

class RfidOpreatingMachine:public RfidOperating
{
public:
    RfidOpreatingMachine(int port);
    ~RfidOpreatingMachine();

private:
    int port;
};

#endif // RFIDOPREATINGMACHINE_H
