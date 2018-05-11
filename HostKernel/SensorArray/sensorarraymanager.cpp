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
    m_numberOfOneArrays = 4;
    m_numberOfTwoArrays = 4;

    for(int i = 0; i < m_numberOfOneArrays; i++)
    {
        m_arrayOneList.append(new SensorArray(i, m_numberOfSensors));
    }

    for(int i = 0; i < m_numberOfTwoArrays; i++)
    {
        m_arrayTwoList.append(new SensorArray(i+4, m_numberOfSensors));
    }
}

void SensorArrayManager::doScan(quint8 address)
{
    logMessage(MSG_INFO, QString("doScan %1").arg(address));

    if(address < 4)
    {
        SensorData *sensorData = new SensorData(address);
        sensorData->addData(m_scanCounter);
        m_chipSelectManager->setChipSelect(address + 8);
        m_arrayOneList.at(address)->getArrayData(*sensorData);
        m_sensorDataListTemp.append(sensorData);

    }
    else if((address >= 4) && (m_scanCounter >= m_arrayOffset))
    {
        SensorData *sensorData = new SensorData(address);
        sensorData->addData(m_scanCounter - m_arrayOffset);
        m_chipSelectManager->setChipSelect(address + 8);
        m_arrayTwoList.at(address >> 4)->getArrayData(*sensorData);
        m_sensorDataList.append(m_sensorDataListTemp.at(m_scanCounter - m_arrayOffset));
        m_sensorDataList.append(sensorData);
    }

    m_scanCounter++;
}

void SensorArrayManager::getScanData(QByteArray &byteArray)
{
    logMessage(MSG_INFO, "getScanData");

    for(int i = 0; i < m_sensorDataList.size(); i++)
    {
        QByteArray byteArrayTemp;
        m_sensorDataList.at(i)->getData(byteArrayTemp);
        byteArray.append(byteArrayTemp);
    }

//    for(int i = 0; i < m_sensorDataList.size(); i++)
//    {
//        delete m_sensorDataList.at(i);
//    }

//    for(int i = 0; i < m_sensorDataListTemp.size(); i++)
//    {
//        delete m_sensorDataListTemp.at(i);
//    }

    m_scanCounter = 0;



}




