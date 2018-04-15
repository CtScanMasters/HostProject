#include "Kernel.h"

#include <QDebug>
#include <QDataStream>


Kernel::Kernel()
:   QObject()

{

    m_kernelServer = new Server(5010);
    m_adcInteruptTimer = new QTimer(this);
    m_adConverter = new MCP3008();
    m_ioExpander = new MCP23S09();
    m_ioMask = 0;

    initializeBCM();
    bcm2835_spi_chipSelect(BCM2835_SPI_CS1);
    m_ioExpander->initialize();
    m_ioExpander->setPorts(0);

    connect(m_adcInteruptTimer, SIGNAL(timeout()), this, SLOT(adcReadSlot()));
    connect(m_kernelServer, SIGNAL(newDataAvailableSignal()), this, SLOT(readServerData()));

    m_adcInteruptTimer->start(100);

}

void Kernel::readServerData()
{
    QByteArray dataInArray;
    QDataStream dataInStream(&dataInArray, QIODevice::ReadWrite);
    m_kernelServer->getReceivedData(dataInArray);

    quint8 sourceMask;
    dataInStream >> sourceMask;

    bcm2835_spi_chipSelect(BCM2835_SPI_CS1);
    m_ioExpander->setPorts(sourceMask);
}

void Kernel::adcReadSlot()
{

    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
    for(int i = 0; i < 8; i++)
    {
        m_adcValueList.append(m_adConverter->readAdc(i));
    }

    QByteArray dataOut;
    QDataStream streamOut(&dataOut, QIODevice::WriteOnly);
    streamOut << m_adcValueList;

    if(m_kernelServer->isClientConnected())
    {
        m_kernelServer->sendData(dataOut);
    }

    m_adcValueList.clear();
}

void Kernel::initializeBCM()
{
    //Initialize Raspberry IO
    if(!bcm2835_init())
    {
            qDebug() << "Initialize BCM2835...FAILED";
    }else
    {

            qDebug() << "Initialize BCM2835...OK";
    }

    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_128); //Approx 1.5Mhz SPI clockrate
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);


    if(!bcm2835_spi_begin())
    {
            qDebug() << "Initialize SPI...FAILED";
    }
    else
    {
            qDebug() << "Initialize SPI...OK";
    }
}
