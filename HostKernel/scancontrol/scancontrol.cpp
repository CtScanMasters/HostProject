#include "scancontrol.h"
#include <QDebug>

ScanControl::ScanControl(QObject *parent)
{
    enableLogging(true);
    setName("ScanControl: ");
    logMessage(MSG_INFO, "build");

    m_arrayOffset = 10;

    m_sourceMuxAddress = 127;
    m_chipSelectPin0 = BCM2835_SPI_CS1;
    m_EN_0 = RPI_V2_GPIO_P1_35;
    m_A0_0 = RPI_V2_GPIO_P1_36;
    m_A1_0 = RPI_V2_GPIO_P1_37;
    m_A2_0 = RPI_V2_GPIO_P1_38;

    m_sensorMuxAddress = 128;
    m_chipSelectPin1 = BCM2835_SPI_CS0;
    m_EN_1 = RPI_V2_GPIO_P1_11;
    m_A0_1 = RPI_V2_GPIO_P1_12;
    m_A1_1 = RPI_V2_GPIO_P1_13;
    m_A2_1 = RPI_V2_GPIO_P1_15;

    m_isInitialized = initialize();
    buildScanControl();

    m_sourceArrayManager->initialize();


    m_chipSelectManager->setChipSelect(0);
    bcm2835_delay(1);

    connect(&m_interruptTimer, SIGNAL(timeout()), this, SLOT(doStuff()));
    m_interruptTimer.start(5000);
}

void ScanControl::doStuff()
{
    for(int i = 0; i < 8; i++)
    {

//        m_sourceArrayManager->setSource(0,0xff);
//        bcm2835_delay(500);

//        m_sourceArrayManager->setSource(0,0x00);
//        bcm2835_delay(500);

        m_sensorArrayManager->doScan(0);
        bcm2835_delay(1000);
        QByteArray byteArray;
        m_sensorArrayManager->getScanData(byteArray);
        qInfo() << byteArray;
    }
}

void ScanControl::buildScanControl()
{
    m_multiplexerSensor = new Multiplexer(m_sourceMuxAddress, m_EN_0, m_A0_0, m_A1_0, m_A2_0);
    m_multiplexerSource = new Multiplexer(m_sensorMuxAddress, m_EN_1, m_A0_1, m_A1_1, m_A1_1);
    m_chipSelectManager = new ChipSelectManager(m_multiplexerSource, m_chipSelectPin1, m_multiplexerSensor, m_chipSelectPin0);
    m_sourceArrayManager = new SourceArrayManager(m_chipSelectManager);
    m_sensorArrayManager = new SensorArrayManager(m_arrayOffset, m_chipSelectManager);
}

bool ScanControl::initialize()
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


