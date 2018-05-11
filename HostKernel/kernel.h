#ifndef KERNEL_H
#define KERNEL_H

#include <QObject>
#include "messagelogger/messagelogger.h"
#include "hardwarecontrol/bcm2835.h"

class Kernel : public QObject, private MessageLogger
{
    Q_OBJECT

    public:
        Kernel();

    public slots:

    private:
        void initialize();
		
	private slots:

	signals:


};

#endif // KERNEL_H
