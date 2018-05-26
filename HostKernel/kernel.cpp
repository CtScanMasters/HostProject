#include "kernel.h"
#include <QDebug>
#include "hardwarecontrol/bcm2835.h"
#include "tcphandler/commandlist.h"

Kernel::Kernel()
{
    m_iAmReady = false;
    m_arrayOffset = 2;
    m_numberOfScans = 10;
    m_scanCounter = 0;
    m_hostPortNumber = 5010;
    m_sendCounter = 0;

    enableLogging(true);
    setName("Kernel: ");
    logMessage(MSG_INFO, "build");

    initializeHardwareControl();

    connect(m_server, SIGNAL(newDataAvailableSignal()), this, SLOT(readTcpData()));

    m_iAmReady = true;
    m_isScanStopped = false;


}

void Kernel::makeScan()
{
    if(m_scanCounter < (m_numberOfScans + m_arrayOffset))
    {
        if(m_scanCounter < m_numberOfScans)
        {
            m_scanDataList.append(new ScanData);
            m_scanDataList.last()->setScanNumber(m_scanCounter);
            qDebug() << m_scanDataList.last()->getData();
            m_scanControl->doScan(0, *m_scanDataList.last());
            logMessage(MSG_INFO, QString("makeScan 1:%1").arg(m_scanCounter));
        }
        if(m_scanCounter >= m_arrayOffset)
        {
            m_scanControl->doScan(4, *m_scanDataList.at(m_scanCounter - m_arrayOffset));
            logMessage(MSG_INFO, QString("makeScan 2:%1").arg(m_scanCounter - m_arrayOffset));
        }

        m_scanCounter++;

        makeScan();
    }
    else
    {
        logMessage(MSG_INFO, QString("scan finished, %1 scans made").arg(m_scanCounter));
        commandHandler(COMMAND_SCAN_NEW_DATA);
    }


}

void Kernel::scanStart()
{
    if(m_iAmReady)
    {
        logMessage(MSG_INFO, "start scan");
        m_iAmReady = false;
        m_isScanStopped = false;
        m_time.start();
        makeScan();
    }
    else
    {
        logMessage(MSG_INFO, "not ready");
        m_bufferOut.append(COMMAND_NOT_READY);
        writeTcpData();
    }
}

void Kernel::scanStop()
{
    logMessage(MSG_INFO, "stop scan");
    m_isScanStopped = true;
    m_iAmReady = true;
    m_scanCounter = 0;
    m_sendCounter = 0;
    m_bufferOut.clear();
    m_bufferIn.clear();

}

void Kernel::getScanData()
{
    logMessage(MSG_INFO, "get scan data");
    dataDelivery();

}

void Kernel::sendReady()
{

}

void Kernel::sendNotReady()
{

}

void Kernel::setScanProgress()
{
    logMessage(MSG_INFO, "set scan progress");
    m_bufferOut.append(COMMAND_SCAN_SET_PROGRESS);
    writeTcpData();
}

void Kernel::newScanData()
{
    qDebug() << "SCAN TIME: " << m_time.elapsed();
    logMessage(MSG_INFO, "new data available");
    m_bufferOut.append(COMMAND_SCAN_NEW_DATA);
    writeTcpData();
}

void Kernel::dataDelivery()
{
    logMessage(MSG_INFO, QString("send new data: %1").arg(m_sendCounter));
    if(m_sendCounter == m_numberOfScans)
    {
        commandHandler(COMMAND_SCAN_DATA_END);
        commandHandler(COMMAND_SCAN_STOP);
        return;
    }
    if(m_scanDataList.size() > 0)
    {
        m_sendCounter++;
        m_bufferOut.append(COMMAND_SCAN_DATA_DELIVERY);
        m_bufferOut.append(m_scanDataList.last()->getData());
        writeTcpData();
        m_scanDataList.removeLast();
    }
}

void Kernel::dataEnd()
{
    logMessage(MSG_INFO, "end of data chain");
    m_bufferOut.append(COMMAND_SCAN_DATA_END);
    writeTcpData();
}

void Kernel::readTcpData()
{
    m_bufferIn.clear();
    m_server->getReceivedData(m_bufferIn);

    commandHandler(m_bufferIn.at(0));
}

void Kernel::writeTcpData()
{
    m_server->sendData(m_bufferOut);
    m_bufferOut.clear();
}

void Kernel::commandHandler(quint8 command)
{
    switch(command)
    {
    case COMMAND_SCAN_START:
        scanStart();
        break;
    case COMMAND_SCAN_STOP:
        scanStop();
        break;
    case COMMAND_SCAN_SET_PROGRESS:
        setScanProgress();
        break;
    case COMMAND_SCAN_GET_DATA:
        getScanData();
        break;
    case COMMAND_SCAN_NEW_DATA:
        newScanData();
        break;
    case COMMAND_SCAN_DATA_DELIVERY:
        dataDelivery();
        break;
    case COMMAND_SCAN_DATA_END:
        dataEnd();
        break;
    case COMMAND_ACTUATOR_FORWARD:
//        actuatorJogForward();
        break;
    case COMMAND_ACTUATOR_BACKWARD:
//        actuatorJogBack();
        break;
    case COMMAND_ACTUATOR_POSITION:
//        actuatorPosition();
        break;
    case COMMAND_ACTUATOR_HOME:
//        actuatorHome();
        break;
    case COMMAND_SENSOR_VALUE:
//        arrayGetSensor();
        break;
    case COMMAND_SOURCE_VALUE:
//        arraySetSource();
        break;
    case COMMAND_READY:
        sendReady();
        break;
    case COMMAND_NOT_READY:
        sendNotReady();
        break;
    default:
        logMessage(MSG_WARNING, "RECEIVED UNKOWN COMMAND");
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
    m_server = new Server(5010);

    return succeeded;
}
