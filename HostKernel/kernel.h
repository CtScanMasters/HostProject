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

    private:
        QTimer m_timer;
        ScanControl *m_scanControl;
		
	private slots:
        void heartbeat();

	signals:


};

#endif // KERNEL_H
