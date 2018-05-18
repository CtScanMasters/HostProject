#ifndef SCANCONTROL_H
#define SCANCONTROL_H

#include <QObject>
#include "messagelogger/messagelogger.h"
#include "hardwarecontrol/bcm2835.h"
#include "hardwarecontrol/chipselectmanager.h"
#include "hardwarecontrol/multiplexer.h"
#include "sourcearray/sourcearraymanager.h"
#include "sensorarray/sensorarraymanager.h"
#include "scandata.h"

class ScanControl : public QObject, private MessageLogger
{
    Q_OBJECT

    public:
        ScanControl(QObject *parent);
        quint16 getScanCounter();

    public slots:
        void doScan(quint8 startAddress, ScanData &scanData);

    private:
        void buildScanControl();

        quint8 m_numberOfArrays;
        quint8 m_numberOfSources;

        quint8 m_sourceMuxAddress;
        quint8 m_chipSelectPin0;
        quint8 m_EN_0;
        quint8 m_A0_0;
        quint8 m_A1_0;
        quint8 m_A2_0;

        quint8 m_sensorMuxAddress;
        quint8 m_chipSelectPin1;
        quint8 m_EN_1;
        quint8 m_A0_1;
        quint8 m_A1_1;
        quint8 m_A2_1;

        Multiplexer *m_multiplexerSensor;
        Multiplexer *m_multiplexerSource;
        ChipSelectManager *m_chipSelectManager;
        SourceArrayManager *m_sourceArrayManager;
        SensorArrayManager *m_sensorArrayManager;

	private slots:


	signals:
        void dataReadySignal(QByteArray);


};

#endif // SCANCONTROL_H
