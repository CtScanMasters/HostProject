#ifndef SOURCEARRAY_H
#define SOURCEARRAY_H

#include <QObject>
#include "messagelogger/messagelogger.h"
#include "hardwarecontrol/MCP23S09.h"

class SourceArray : public QObject, private MessageLogger
{
    Q_OBJECT

    public:
        SourceArray(quint8 address);
        void setAddress(quint8 address);
        quint8 getAddress();
        void setChannel(quint8 channel);
        void clearChannels();
        quint8 getChannel();
        void initialize();

    public slots:

    private:
        MCP23S09 *m_ioExpander;
        quint8 m_address;
        quint8 m_channelMask;
		
	private slots:

	signals:


};

#endif // SOURCEARRAY_H
