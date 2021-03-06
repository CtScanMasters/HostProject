#ifndef SENSORARRAY_H
#define SENSORARRAY_H

#include <QObject>

#include "messagelogger/messagelogger.h"
#include "hardwarecontrol/MCP3008.h"
#include "scancontrol/scandata.h"

class SensorArray : public QObject, private MessageLogger
{
    Q_OBJECT

    public:
        SensorArray(quint8 address, quint8 numberOfSensors);
        void getArrayData(ScanData &scanData, quint8 address);

    public slots:

    private:
        quint8 m_address;
        quint8 m_numberOfSensors;
        MCP3008 *m_adConverter;

	private slots:

	signals:


};

#endif // SENSORARRAY_H
