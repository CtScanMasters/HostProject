#include "chipselectmanager.h"
#include <QDebug>

ChipSelectManager::ChipSelectManager(Multiplexer *muxCe0, quint8 chipSelect0, Multiplexer *muxCe1, quint8 chipSelect1)
    : m_muxCs0(muxCe0), m_chipSelectPin0(chipSelect0), m_muxCs1(muxCe1), m_chipSelectPin1(chipSelect1)
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
        bcm2835_spi_chipSelect(m_chipSelectPin1);
        m_muxCs1->setChannel(m_selectedAddress);
    }
    else if((m_selectedAddress > 7) && (m_selectedAddress < 16))
    {
        m_selectedAddress = address - 8;
        bcm2835_spi_chipSelect(m_chipSelectPin0);
        m_muxCs0->setChannel(m_selectedAddress);
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
