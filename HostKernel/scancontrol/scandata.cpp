#include "scandata.h"
#include <QDebug>

ScanData::ScanData()
{
    m_scanNumber = 0;
}

void ScanData::setScanNumber(quint16 scanNumber)
{
    m_logName = QString("scandata %1: ").arg(scanNumber);
    setName(m_logName);
    logMessage(MSG_INFO, "new data");

    m_scanNumber = scanNumber;    
}

quint16 ScanData::getScanNumber()
{
    return m_scanNumber;
}

void ScanData::addArrayScan(quint16 address, quint16 source)
{
    addData(m_scanNumber);
    addData(address);
    addData(source);
}

void ScanData::addSensorData(quint16 data)
{
   addData(data);
}

QByteArray& ScanData::getData()
{
    return m_scanDataArray;
}

void ScanData::addData(quint16 data)
{
    m_scanDataArray.append( (data >> 8) & 0xFF );
    m_scanDataArray.append( data & 0xFF );
}
