#include "MCP3008.h"
#include <QDebug>

MCP3008::MCP3008(quint8 address)
    : m_address(address)
{
    enableLogging(true);
    setName(QString("ADconverter %1: ").arg(m_address));
    logMessage(MSG_INFO, "build");

    initialize();
}

void MCP3008::setAddress(quint8 address)
{
    m_address = address;
    setName(QString("ADconverter %1: ").arg(m_address));
    logMessage(MSG_INFO, QString("setaddress: %1").arg(m_address));
}

quint8 MCP3008::getAddress()
{
    return m_address;
}

bool MCP3008::initialize()
{
    m_txBuffer[0] = 0x00;
    m_txBuffer[1] = 0x00;
    m_txBuffer[2] = 0x00;

    m_rxBuffer[0] = 0x00;
    m_rxBuffer[1] = 0x00;
    m_rxBuffer[2] = 0x00;

    return true;
}

quint16 MCP3008::getData(quint8 channel)
{
    uint16_t adcValue = 0;

    channel = (channel | 0x18) << 3;
    m_txBuffer[0] =  channel;

    bcm2835_spi_transfernb(m_txBuffer, m_rxBuffer, 3);

    adcValue = 0x3FF & ((m_rxBuffer[0] & 0x01) << 9 |
                        (m_rxBuffer[1] & 0xFF) << 1 |
                        (m_rxBuffer[2] & 0x80) >> 7 );

    return adcValue;
}

