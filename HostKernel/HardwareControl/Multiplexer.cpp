#include "multiplexer.h"
#include <QDebug>

Multiplexer::Multiplexer(quint8 address, quint8 enable, quint8 A0, quint8 A1, quint8 A2)
    : m_address(address), m_enable(enable), m_A0(A0), m_A1(A1), m_A2(A2)
{
    enableLogging(true);

    m_currentChannel = 0;
    setName(QString("Multiplexer %1: ").arg(m_address));
    logMessage(MSG_INFO, QString("build: channels: EN=%1 A0=%2, A1=%3, A2=%4").arg(m_enable).arg(m_A0).arg(m_A1).arg(m_A2));
}

void Multiplexer::initialize()
{
    bcm2835_gpio_fsel(m_enable, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(m_A0, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(m_A1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(m_A2, BCM2835_GPIO_FSEL_OUTP);

    bcm2835_gpio_write(m_enable, 0);
    bcm2835_gpio_write(m_A0, 0);
    bcm2835_gpio_write(m_A1, 0);
    bcm2835_gpio_write(m_A2, 0);
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

    if(m_currentChannel == 255)
    {
        bcm2835_gpio_write(m_enable, HIGH);
        logMessage(MSG_INFO, "setChannel: mux disabled");
    }
    else
    {
        bcm2835_gpio_write(m_enable, LOW);

//        logMessage(MSG_INFO, QString("setChannel: %1 : mask: %2 %3 %4")
//                    .arg(m_currentChannel)
//                    .arg((channel & 0x04) >> 2)
//                    .arg((channel & 0x02) >> 1)
//                    .arg((channel & 0x01) >> 0));

        bcm2835_gpio_write(m_A0, (channel & 0x01) >> 0);
        bcm2835_gpio_write(m_A1, (channel & 0x02) >> 1);
        bcm2835_gpio_write(m_A2, (channel & 0x04) >> 2);
    }

}

quint8 Multiplexer:: getChannel()
{
    return m_currentChannel;
}
