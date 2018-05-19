#include "kernel.h"
#include <QDebug>
#include "hardwarecontrol/bcm2835.h"

Kernel::Kernel()
{
    enableLogging(true);
    setName("Kernel: ");
    logMessage(MSG_INFO, "build");

    initializeHardwareControl();

    connect(&m_scanTimer, SIGNAL(timeout()), this, SLOT(makeScan()));
    m_scanTimer.start(2000);

}

void Kernel::processData()
{
    logMessage(MSG_INFO, "processData");
}

void Kernel::makeScan()
{
    logMessage(MSG_INFO, "makeScan");

    qWarning() << "YEAH----------------------------0000000";

    m_scanDataList.append(new ScanData);
    m_scanDataList.last()->setScanNumber(m_scanDataList.size());

    m_scanControl->doScan(0, *m_scanDataList.last());

    QByteArray byteArray;
    byteArray = m_scanDataList.last()->getData();

    QList<QByteArray> arrayList;
    arrayList = byteArray.split(':');

    for(int i = 0; i < arrayList.size(); i++)
    {
        qDebug() << arrayList.at(i);
    }

    qWarning() << "YEAH----------------------------44444444";

    m_scanDataList.append(new ScanData);
    m_scanDataList.last()->setScanNumber(m_scanDataList.size());

    m_scanControl->doScan(4, *m_scanDataList.last());
    byteArray = m_scanDataList.last()->getData();
    arrayList = byteArray.split(':');

    for(int i = 0; i < arrayList.size(); i++)
    {
        qDebug() << arrayList.at(i);
    }
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
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_1024); //Approx 1.5Mhz SPI clockrate
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

    m_scanControl = new ScanControl(this);

    return succeeded;
}
