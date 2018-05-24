#include "sensorarray.h"
#include <QDebug>

SensorArray::SensorArray(quint8 address, quint8 numberOfSensors)
    : m_address(address), m_numberOfSensors(numberOfSensors)
{
    setName(QString("SensorArray %1: ").arg(m_address));
    logMessage(MSG_INFO, "build");
    enableLogging(false);

    m_adConverter = new MCP3008(m_address);

}

void SensorArray::getArrayData(ScanData &scanData)
{
    //logMessage(MSG_INFO, "getArrayData");
    for(int i = 0; i < m_numberOfSensors; i++)
    {
        scanData.addSensorData(m_adConverter->getData(i));
        //qDebug() << m_adConverter->getData(i);
    }
}




