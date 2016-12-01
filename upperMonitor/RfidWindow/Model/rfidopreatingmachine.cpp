#include "rfidopreatingmachine.h"

RfidOpreatingMachine::RfidOpreatingMachine(int port):
    RfidOperating()
{
    this->port = port;

    intialPort(this->port);
    controlBeep(10);
    setWorkType();
}

RfidOpreatingMachine::~RfidOpreatingMachine()
{
    closePort();
}

