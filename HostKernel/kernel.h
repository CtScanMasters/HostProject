#ifndef KERNEL_H
#define KERNEL_H

#include <QObject>
#include <QTimer>
#include "messagelogger/messagelogger.h"
#include "hardwarecontrol/bcm2835.h"
#include "scancontrol/scancontrol.h"


class Kernel : public QObject, private MessageLogger
{
    Q_OBJECT

    public:
        Kernel();

    public slots:
        void start();
        void processData(QByteArray byteArray);

    private:
        QTimer m_heartBeatTimer;
        QTimer m_scanTimer;
        ScanControl *m_scanControl;
        bool m_hardwareInitialized;

        bool initializeHardwareControl();
		
	private slots:
        void heartbeat();
        void makeScan();

	signals:


};

#endif // KERNEL_H
