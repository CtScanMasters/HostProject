#include "sourcearray.h"
#include <QDebug>

SourceArray::SourceArray(quint8 address)
    : m_address(address)
{
    m_ioExpander = new MCP23S09(m_address);

    setName(QString("SourceArray %1: ").arg(m_address));
    logMessage(MSG_INFO, "build");
    enableLogging(false);
}

void SourceArray::setAddress(quint8 address)
{
    m_address = address;
    setName(QString("SourceArray %1: ").arg(m_address));
}

quint8 SourceArray::getAddress()
{
    return m_address;
}

void SourceArray::setChannel(quint8 channel)
{    
    m_channelMask = 0x01 << channel;
    m_ioExpander->setChannel(m_channelMask);
}

quint8 SourceArray::getChannel()
{
    return m_channelMask;
}

void SourceArray::initialize()
{
    m_ioExpander->initialize();
}
