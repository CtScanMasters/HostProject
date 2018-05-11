#ifndef CHIPSELECTMANAGER_H
#define CHIPSELECTMANAGER_H

#include <QObject>
#include <QTimer>
#include "messagelogger/messagelogger.h"
#include "hardwarecontrol/multiplexer.h"

class ChipSelectManager : public QObject, private MessageLogger
{
    Q_OBJECT

    public:
        ChipSelectManager(Multiplexer *muxCe0, quint8 chipSelect0, Multiplexer *muxCe1, quint8 chipSelect1);
        void setChipSelect(quint8 address);
        quint8 getChipSelect();

    public slots:

    private:
        Multiplexer *m_muxCs0;
        quint8 m_chipSelectPin0;

        Multiplexer *m_muxCs1;
        quint8 m_chipSelectPin1;

        quint8 m_selectedAddress;


		
	private slots:


	signals:


};

#endif // CHIPSELECTMANAGER_H
