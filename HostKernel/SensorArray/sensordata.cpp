#include "sensordata.h"
#include <QDebug>

SensorData::SensorData(quint8 address)
    : m_address(address)
{
    addData(address);
}

void SensorData::addData(quint16 data)
{
    m_dataArray.append(data);
}

void SensorData::getData(QByteArray &byteArray)
{
    qDebug() << "Data: " << m_dataArray;
    byteArray.append(m_dataArray);
    byteArray.append(";");
}

