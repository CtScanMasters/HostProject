#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <QList>

class SensorData
{

    public:
        SensorData(quint8 address);
        void addData(quint16 data);
        void getData(QByteArray &byteArray);

    private:
        quint8 m_address;
        QByteArray m_dataArray;
		



};

#endif // SENSORDATA_H
