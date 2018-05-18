#include "scandata.h"
#include <QDebug>

ScanData::ScanData()
{
    m_scanNumber = 0;
}

void ScanData::setScanNumber(quint16 scanNumber)
{
    m_scanNumber = scanNumber;
    m_scanDataArray.append(m_scanNumber);
}

quint16 ScanData::getScanNumber()
{
    return m_scanNumber;
}

void ScanData::addArrayScan(quint16 address, quint16 source)
{
    m_scanDataArray.append(address);
    m_scanDataArray.append(source);
}

void ScanData::addSensorData(quint16 data)
{
    m_scanDataArray.append(data);
}

QByteArray& ScanData::getData()
{
    return m_scanDataArray;
}
