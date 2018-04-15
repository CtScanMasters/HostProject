#ifndef MCP23S09_H
#define MCP23S09_H

#include "bcm2835.h"

class MCP23S09
{
private:
    char txBuf[3];
    char rxBuf[3];

public:
    MCP23S09();
    void initialize();
    void setPorts(uint8_t portMask);
};

#endif // MCP23S09_H
