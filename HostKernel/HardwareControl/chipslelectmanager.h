#ifndef CHIPSELECTMANAGER_H
#define CHIPSELECTMANAGER_H

#include <QObject>
#include "messagelogger/messagelogger.h"
#include "hardwarecontrol/multiplexer.h"

class ChipSelectManager : public QObject, private MessageLogger
{
    Q_OBJECT

    public:
        ChipSelectManager(Multiplexer *muxCe0, Multiplexer *muxCe1);
        void setChipSelect(quint8 address);
        quint8 getChipSelect();

    public slots:

    private:
        Multiplexer *m_muxCs0;
        Multiplexer *m_muxCs1;
        quint8 m_selectedAddress;
		
	private slots:

	signals:


};

#endif // CHIPSELECTMANAGER_H
