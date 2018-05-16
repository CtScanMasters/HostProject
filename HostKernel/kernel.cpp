#include "kernel.h"
#include <QDebug>
#include "hardwarecontrol/bcm2835.h"

Kernel::Kernel()
{
    enableLogging(true);
    setName("Kernel: ");
    logMessage(MSG_INFO, "build");

    m_hardwareInitialized = false;

}

void Kernel::processData(QByteArray byteArray)
{
    logMessage(MSG_INFO, "processData");

//    qDebug() << "KERNEL: " << byteArray;

//    quint8 byte0 = 0;
//    quint8 byte1 = 0;
//    quint8 address = 0;
//    quint8 sourceNumber = 0;
//    quint16 scanCounter = 0;


//    byte0 = byteArray.at(0);
//    byte1 = byteArray.at(1);

//    scanCounter = ((scanCounter | byte1) << 8) | byte0;
//    address = byteArray.at(2);
//    sourceNumber = byteArray.at(3);

//    logMessage(MSG_INFO, QString("Counter: %1, address: %2, source: %3")
//               .arg(scanCounter).arg(address).arg(sourceNumber));

//    for(int i = 0; i < (byteArray.size() - 1); i++)
//    {
//        byte0 = byteArray.at(i);
//        byte1 = byteArray.at(i+1);
//        quint16 data = (byte0 << 8) + byte1;

//        logMessage(MSG_INFO, QString("Data: %1 = %2").arg(i).arg(data));
//    }

}

void Kernel::makeScan()
{
    m_scanControl->doScan();
}

void Kernel::heartbeat()
{
    if(m_hardwareInitialized)
    {
        logMessage(MSG_INFO, "heartbeat");
    }
    else
    {
        logMessage(MSG_INFO, "initialize hardware controller");
        start();
    }
}


void Kernel::start()
{
    logMessage(MSG_INFO, "start");

    m_hardwareInitialized = initializeHardwareControl();

    if(m_hardwareInitialized)
    {
        m_scanControl = new ScanControl(this);
        m_scanControl->newScan();

        connect(&m_scanTimer, SIGNAL(timeout()), this, SLOT(makeScan()));
        connect(m_scanControl, SIGNAL(dataReadySignal(QByteArray)), this, SLOT(processData(QByteArray)));

        m_scanTimer.start(2500);
    }
    else
    {
        logMessage(MSG_WARNING, "start: could not initialize hardware controller!!");
    }

    connect(&m_heartBeatTimer, SIGNAL(timeout()), this, SLOT(heartbeat()));
    m_heartBeatTimer.start(10000);
}

bool Kernel::initializeHardwareControl()
{
    bool succeeded = false;
    //Initialize Raspberry IO
    if(!bcm2835_init())
    {
            logMessage(MSG_INFO, "Initialize BCM2835...FAILED");
            succeeded = false;
            return succeeded;
    }
    else
    {
            logMessage(MSG_INFO, "Initialize BCM2835...OK");
            succeeded = true;
    }

    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_128); //Approx 1.5Mhz SPI clockrate
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);

    if(!bcm2835_spi_begin())
    {
            logMessage(MSG_INFO, "Initialize SPI...FAILED");
            succeeded = false;
            return succeeded;
    }
    else
    {
            logMessage(MSG_INFO, "Initialize SPI...OK");
            succeeded = true;
    }

    return succeeded;
}
