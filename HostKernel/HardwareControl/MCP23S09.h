#ifndef MCP23S08_H
#define MCP23S08_H

#include <QObject>
#include "messagelogger/messagelogger.h"
#include "hardwarecontrol/bcm2835.h"

class MCP23S08 : public QObject, private MessageLogger
{
    Q_OBJECT

    public:

        MCP23S08(quint8 address);
        void setAddress(quint8 address);
        quint8 getAddress();
        void setChannel(quint8 channelMask);
        quint8 getChannel();

    public slots:

    private:
        QString m_logName;
        bool initialize();
        quint8 m_address;
        quint8 m_channelMask;

        char m_txBuffer[3];
        char m_rxBuffer[3];
		
	private slots:

	signals:


};

#endif // MCP23S08_H
