#ifndef SENSORARRAYMANAGER_H
#define SENSORARRAYMANAGER_H

#include <QObject>
#include <QList>
#include "messagelogger/messagelogger.h"
#include "sensorarray.h"
#include "hardwarecontrol/chipselectmanager.h"
#include "scancontrol/scandata.h"

class SensorArrayManager : public QObject, private MessageLogger
{
    Q_OBJECT

    public:
        SensorArrayManager(ChipSelectManager *chipSelectManager);
        void scanArray(quint8 address, ScanData &scanData);

    public slots:

    private:
        ChipSelectManager *m_chipSelectManager;
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
