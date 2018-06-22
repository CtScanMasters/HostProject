#include "MCP23S09.h"
#include <QDebug>

MCP23S09::MCP23S09(quint8 address)
    : m_address(address)
{
    m_channelMask = 0;

    enableLogging(true);
    setName(QString("IOexpander %1: ").arg(m_address));
    logMessage(MSG_INFO, "build");
}

void MCP23S09::setAddress(quint8 address)
{
    m_address = address;
    setName(QString("IOexpander %1: ").arg(m_address));
    logMessage(MSG_INFO, QString("setaddress: %1").arg(m_address));
}

quint8 MCP23S09::getAddress()
{
    return m_address;
}

bool MCP23S09::initialize()
{
    m_txBuffer[0] = 0x40;
    m_txBuffer[1] = 0x00;
    m_txBuffer[2] = 0x00;

    m_rxBuffer[0] = 0x00;
    m_rxBuffer[1] = 0x00;
    m_rxBuffer[2] = 0x00;

    bcm2835_spi_transfernb(m_txBuffer, m_rxBuffer, 3);

//    m_txBuffer[0] = 0x40;
//    m_txBuffer[1] = 0x06;
//    m_txBuffer[2] = 0xFF;

//    m_rxBuffer[0] = 0x00;
//    m_rxBuffer[1] = 0x00;
//    m_rxBuffer[2] = 0x00;

//    bcm2835_spi_transfernb(m_txBuffer, m_rxBuffer, 3);

    return true;
}

void MCP23S09::setChannel(quint8 channelMask)
{
    m_txBuffer[0] = 0x40;
    m_txBuffer[1] = 0x09;
    m_txBuffer[2] = channelMask;

//    logMessage(MSG_INFO, QString::number(channelMask, 16));

    bcm2835_spi_transfernb(m_txBuffer, m_rxBuffer, 3);
}

quint8 MCP23S09::getChannel()
{
    //quint8 channelLevel = 0;
    //Read channel level here

    return m_channelMask;
}
