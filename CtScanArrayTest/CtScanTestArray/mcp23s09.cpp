#include "mcp23s09.h"

MCP23S09::MCP23S09()
{

}

void MCP23S09::initialize()
{
    txBuf[0] = 0x40;
    txBuf[1] = 0x00;
    txBuf[2] = 0x00;

    rxBuf[0] = 0x00;
    rxBuf[1] = 0x00;
    rxBuf[1] = 0x00;

    bcm2835_spi_transfernb(txBuf, rxBuf, 3);
}

void MCP23S09::setPorts(uint8_t portMask)
{
    txBuf[0] = 0x40;
    txBuf[1] = 0x12;
    txBuf[2] = portMask;
    bcm2835_spi_transfernb(txBuf, rxBuf, 3);
}
