#ifndef SENSORARRAYMANAGER_H
#define SENSORARRAYMANAGER_H

#include <QObject>
#include <QList>
#include "messagelogger/messagelogger.h"
#include "sensorarray.h"
#include "sensordata.h"

class SensorArrayManager : public QObject, private MessageLogger
{
    Q_OBJECT

    public:
        SensorArrayManager(quint32 arrayOffset);
        void doScan(quint8 address);
        void getScanData(QByteArray &byteArray);

    public slots:

    private:
        quint8 m_arrayOffset;
        quint16 m_scanCounter;
        quint8 m_numberOfSensors;
        quint8 m_numberOfArrays;
        quint8 m_numberOfOneArrays;
        quint8 m_numberOfTwoArrays;
        QList<SensorArray *> m_arrayOneList;
        QList<SensorArray *> m_arrayTwoList;
        QList<SensorData *> m_sensorDataList;
        QList<SensorData *> m_sensorDataListTemp;
		
	private slots:

	signals:


};

#endif // SENSORARRAYMANAGER_H
