#include "sensorarraymanager.h"
#include <QDebug>

SensorArrayManager::SensorArrayManager(ChipSelectManager *chipSelectManager)
    : m_chipSelectManager(chipSelectManager)
{
    setName("SensorArrayManager: ");
    logMessage(MSG_INFO, "build");
    enableLogging(false);

    m_scanCounter = 0;
    m_numberOfSensors = 8;
    m_numberOfArrays = 8;

    for(int i = 0; i < m_numberOfArrays; i++)
    {
        m_sensorArrayList.append(new SensorArray(i, m_numberOfSensors));

    }
}

void SensorArrayManager::scanArray(quint8 address, ScanData &scanData)
{
    m_chipSelectManager->setChipSelect(address + 8);

    logMessage(MSG_INFO, QString("scanArray %1").arg(address));

    m_sensorArrayList.at(address)->getArrayData(scanData, address);
}





