#include "multiplexer.h"
#include <QDebug>

Multiplexer::Multiplexer(quint8 address, quint8 A0, quint8 A1, quint8 A2)
    : m_address(address), m_A0(A0), m_A1(A1), m_A2(A2)
{
    enableLogging(true);

    m_currentChannel = 0;
    setName(QString("Multiplexer %1: ").arg(m_address));
    logMessage(MSG_INFO, QString("build: channels: %1, %2, %3").arg(m_A0).arg(m_A1).arg(m_A2));
}

void Multiplexer::setAddress(quint8 address)
{
    m_address = address;
    setName(QString("Multiplexer %1: ").arg(m_address));
    logMessage(MSG_INFO, QString("setaddress: %1").arg(m_address));
}

quint8 Multiplexer::getAddress()
{
    return m_address;
}

void Multiplexer::setChannel(quint8 channel)
{
    m_currentChannel = channel;
    logMessage(MSG_INFO, QString("setChannel: %1").arg(m_currentChannel));
    //Set the IO pins here
    //set > m_currentChannel;
}

quint8 Multiplexer:: getChannel()
{
    return m_currentChannel;
}
