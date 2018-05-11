#include "MCP23S09.h"
#include <QDebug>

MCP23S08::MCP23S08(quint8 address)
    : m_address(address)
{
    m_channelMask = 0;

    enableLogging(true);
    setName(QString("IOexpander %1: ").arg(m_address));
    logMessage(MSG_INFO, "build");
}

void MCP23S08::setAddress(quint8 address)
{
    m_address = address;
    setName(QString("IOexpander %1: ").arg(m_address));
    logMessage(MSG_INFO, QString("setaddress: %1").arg(m_address));
}

quint8 MCP23S08::getAddress()
{
    return m_address;
}

bool MCP23S08::initialize()
{
    //SPI initialize IC here
}

void MCP23S08::setChannel(quint8 channelMask)
{
    //SPI communicates channel here
}

quint8 MCP23S08::getChannel()
{
    quint8 channelLevel = 0;
    //Read channel level here

    return m_channelMask;
}
