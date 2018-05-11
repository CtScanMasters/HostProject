#include "MCP3008.h"
#include <QDebug>

MCP3008::MCP3008(quint8 address)
    : m_address(address)
{
    enableLogging(true);
    setName(QString("ADconverter %1: ").arg(m_address));
    logMessage(MSG_INFO, "build");
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

}

quint16 MCP3008::getData(quint8 channel)
{
    quint16 data = 0;
    setChannel(channel);

    return data;
}

void MCP3008::setChannel(quint8 channel)
{
    //SPI communicates channel here
}
