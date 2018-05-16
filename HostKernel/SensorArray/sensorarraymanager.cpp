#include "sensorarraymanager.h"
#include <QDebug>

SensorArrayManager::SensorArrayManager(quint32 arrayOffset, ChipSelectManager *chipSelectManager)
    : m_arrayOffset(arrayOffset), m_chipSelectManager(chipSelectManager)
{
    enableLogging(true);
    setName("SensorArrayManager: ");
    logMessage(MSG_INFO, "build");

    m_scanCounter = 0;
    m_numberOfSensors = 8;
    m_numberOfArrays = 8;

    for(int i = 0; i < m_numberOfArrays; i++)
    {
        m_sensorArrayList.append(new SensorArray(i, m_numberOfSensors));
    }
}

void SensorArrayManager::scanArray(quint8 address, QByteArray &byteArray)
{
    logMessage(MSG_INFO, QString("scanArray %1").arg(address));

    m_chipSelectManager->setChipSelect(address + 8);

    for(int i = 0; i < m_numberOfSensors; i++)
    {
        m_sensorArrayList.at(address)->getArrayData(byteArray);
    }
}





