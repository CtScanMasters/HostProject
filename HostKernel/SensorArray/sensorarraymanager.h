#ifndef SENSORARRAYMANAGER_H
#define SENSORARRAYMANAGER_H

#include <QObject>
#include <QList>
#include "messagelogger/messagelogger.h"
#include "sensorarray.h"
#include "sensordata.h"
#include "hardwarecontrol/chipselectmanager.h"

class SensorArrayManager : public QObject, private MessageLogger
{
    Q_OBJECT

    public:
        SensorArrayManager(quint32 arrayOffset, ChipSelectManager *chipSelectManager);
        void scanArray(quint8 address, QByteArray &byteArray);

    public slots:

    private:
        ChipSelectManager *m_chipSelectManager;
        quint8 m_arrayOffset;
        quint16 m_scanCounter;
        quint8 m_numberOfSensors;
        quint8 m_numberOfArrays;
        quint8 m_numberOfOneArrays;
        quint8 m_numberOfTwoArrays;

        QList<SensorArray *> m_sensorArrayList;

        QList<QByteArray> m_scanDataArrayListFirstRing;
        QList<QByteArray> m_scanDataArrayList;

	private slots:

	signals:


};

#endif // SENSORARRAYMANAGER_H
