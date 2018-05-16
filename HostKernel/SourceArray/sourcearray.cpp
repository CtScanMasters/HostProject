#include "sourcearray.h"
#include <QDebug>

SourceArray::SourceArray(quint8 address)
    : m_address(address)
{
    m_ioExpander = new MCP23S08(m_address);

    enableLogging(true);
    setName(QString("SourceArray %1: ").arg(m_address));
    logMessage(MSG_INFO, "build");
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

void SourceArray::setChannel(quint8 channelMask)
{    
    m_channelMask = channelMask;
    m_ioExpander->setChannel(channelMask);
}

quint8 SourceArray::getChannel()
{
    return m_channelMask;
}

void SourceArray::initialize()
{
    m_ioExpander->initialize();
}
