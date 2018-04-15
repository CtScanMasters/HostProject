#include "mcp3008.h"

MCP3008::MCP3008()
{
    txBuf[0] = 0x00;
    txBuf[1] = 0x00;
    txBuf[2] = 0x00;

    rxBuf[0] = 0x00;
    rxBuf[1] = 0x00;
    rxBuf[2] = 0x00;
}

uint16_t MCP3008::readAdc(uint8_t adcPort)
{

    uint16_t adcValue = 0;

    adcPort = (adcPort | 0x18) << 3;
    txBuf[0] =  adcPort;

    bcm2835_spi_transfernb(txBuf, rxBuf, 3);

    adcValue = 0x3FF & ((rxBuf[0] & 0x01) << 9 |
                        (rxBuf[1] & 0xFF) << 1 |
                        (rxBuf[2] & 0x80) >> 7 );

    return adcValue;
}
