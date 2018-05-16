#include "scancontrol.h"
#include <QDebug>

ScanControl::ScanControl(QObject *parent)
{
    enableLogging(true);
    setName("ScanControl: ");
    logMessage(MSG_INFO, "build");

    m_arrayOffset = 3;
    m_numberOfArrays = 8;
    m_numberOfSources = 8;
    m_scanCounter = 0;

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

    buildScanControl();

    m_sourceArrayManager->initialize();

}

void ScanControl::newScan()
{
    logMessage(MSG_INFO, "newScan");

    //scanDataList.clear();
    m_scanCounter = 0;
}

void ScanControl::doScan()
{
    logMessage(MSG_INFO, "doScan");

    quint8 sourceMask = 0x01;

    for(quint8 arrayAddress = 0; arrayAddress < m_numberOfArrays; arrayAddress++)
    {
        for(quint8 sourceNumber = 0; sourceNumber < m_numberOfSources; sourceNumber++)
        {
            m_sourceArrayManager->setSource(arrayAddress, (sourceMask << sourceNumber));

            //Wachtijd voor sensoren om op sterkte te komen????

            QByteArray sensorDataArray;
            sensorDataArray.append(m_scanCounter);
            sensorDataArray.append(arrayAddress);
            sensorDataArray.append(sourceNumber);
            m_sensorArrayManager->scanArray(arrayAddress, sensorDataArray);

            if((m_scanCounter > m_arrayOffset) && arrayAddress >= 4)
            {


//                emit dataReadySignal(tempArray);
            }
            else if(arrayAddress < 4)
            {

            }
        }
    }
    m_scanCounter++;
}

quint16 ScanControl::getScanCounter()
{
    return m_scanCounter;
}

void ScanControl::buildScanControl()
{
    m_multiplexerSensor = new Multiplexer(m_sourceMuxAddress, m_EN_0, m_A0_0, m_A1_0, m_A2_0);
    m_multiplexerSource = new Multiplexer(m_sensorMuxAddress, m_EN_1, m_A0_1, m_A1_1, m_A2_1);
    m_chipSelectManager = new ChipSelectManager(m_multiplexerSource, m_chipSelectPin1, m_multiplexerSensor, m_chipSelectPin0);
    m_sourceArrayManager = new SourceArrayManager(m_chipSelectManager);
    m_sensorArrayManager = new SensorArrayManager(m_arrayOffset, m_chipSelectManager);

}




