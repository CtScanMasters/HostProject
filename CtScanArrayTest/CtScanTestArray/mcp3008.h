#ifndef MCP3008_H
#define MCP3008_H

#include "bcm2835.h"

class MCP3008
{
private:
    char txBuf[3];
    char rxBuf[3];

public:
    MCP3008();
    uint16_t readAdc(uint8_t adcPort);
};

#endif // MCP3008_H
