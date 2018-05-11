#include "chipslelectmanager.h"
#include <QDebug>

ChipSelectManager::ChipSelectManager(Multiplexer *muxCe0, Multiplexer *muxCe1)
    : m_muxCs0(muxCe0), m_muxCs1(muxCe1)
{
    enableLogging(true);

    m_selectedAddress = 0;

    setName(QString("ChipSelector: "));
    logMessage(MSG_INFO, "build");
}

void ChipSelectManager::setChipSelect(quint8 address)
{
    m_selectedAddress = address;
    logMessage(MSG_INFO, QString("setChipSelect: %1").arg(m_selectedAddress));

    if((m_selectedAddress >= 0) && (m_selectedAddress < 8))
    {
        m_muxCs0->setChannel(m_selectedAddress);
    }
    else if((m_selectedAddress > 7) && (m_selectedAddress < 16))
    {
        m_selectedAddress = address >> 7;
        m_muxCs1->setChannel(m_selectedAddress);
    }
    else
    {
        logMessage(MSG_WARNING, "setChipSelect: address not valid");
        return;
    }

}

quint8 ChipSelectManager::getChipSelect()
{
    return m_selectedAddress;
}
