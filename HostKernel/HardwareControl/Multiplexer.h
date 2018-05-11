#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H

#include <QObject>
#include "messagelogger/messagelogger.h"
#include "bcm2835.h"

class Multiplexer : public QObject, private MessageLogger
{
    Q_OBJECT

    public:
        Multiplexer(quint8 address, quint8 enable, quint8 A0, quint8 A1, quint8 A2);
        void initialize();
        void setAddress(quint8 address);
        quint8 getAddress();
        void setChannel(quint8 channel);
        quint8 getChannel();

    public slots:

    private:
        quint8 m_address;
        quint8 m_enable;
        quint8 m_A0;
        quint8 m_A1;
        quint8 m_A2;
        quint8 m_currentChannel;
		
	private slots:

	signals:


};

#endif // MULTIPLEXER_H
