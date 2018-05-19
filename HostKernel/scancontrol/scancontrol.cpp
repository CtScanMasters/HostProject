#include "scancontrol.h"
#include <QDebug>
#include "hardwarecontrol/bcm2835.h"

ScanControl::ScanControl(QObject *parent)
{
    enableLogging(true);
    setName("ScanControl: ");
    logMessage(MSG_INFO, "build");

    m_numberOfArrays = 8;
    m_numberOfSources = 8;

    m_sourceMuxAddress = 127;
    m_chipSelectPin1 = BCM2835_SPI_CS1;
    m_EN_1 = RPI_V2_GPIO_P1_11;
    m_A0_1 = RPI_V2_GPIO_P1_12;
    m_A1_1 = RPI_V2_GPIO_P1_13;
    m_A2_1 = RPI_V2_GPIO_P1_15;

    m_sensorMuxAddress = 128;
    m_chipSelectPin0 = BCM2835_SPI_CS0;
    m_EN_0 = RPI_V2_GPIO_P1_35;
    m_A0_0 = RPI_V2_GPIO_P1_36;
    m_A1_0 = RPI_V2_GPIO_P1_37;
    m_A2_0 = RPI_V2_GPIO_P1_38;

    buildScanControl();    


}

void ScanControl::doScan(quint8 startAddress, ScanData &scanData)
{
    logMessage(MSG_INFO, QString("doScan: %1").arg(startAddress));

    for(quint8 arrayAddress = startAddress; arrayAddress < (startAddress + 4); arrayAddress++)
    {
        for(quint8 sourceNumber = 0; sourceNumber < m_numberOfSources; sourceNumber++)
        {
            m_sourceArrayManager->setSource(arrayAddress, sourceNumber);

            //Wachtijd voor sensoren om op sterkte te komen????

            scanData.addArrayScan(arrayAddress, sourceNumber);

            m_sensorArrayManager->scanArray(arrayAddress, scanData);
        }
    }
}

void ScanControl::buildScanControl()
{
    m_multiplexerSensor = new Multiplexer(m_sourceMuxAddress, m_EN_0, m_A0_0, m_A1_0, m_A2_0);
    m_multiplexerSource = new Multiplexer(m_sensorMuxAddress, m_EN_1, m_A0_1, m_A1_1, m_A2_1);
    m_chipSelectManager = new ChipSelectManager(m_multiplexerSource, m_chipSelectPin0, m_multiplexerSensor, m_chipSelectPin1);
    m_sourceArrayManager = new SourceArrayManager(m_chipSelectManager);
    m_sensorArrayManager = new SensorArrayManager(m_chipSelectManager);

    m_sourceArrayManager->initialize();
}




