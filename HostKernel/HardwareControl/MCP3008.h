#ifndef MCP3008_H
#define MCP3008_H

#include <QObject>
#include "messagelogger/messagelogger.h"
#include "hardwarecontrol/bcm2835.h"

class MCP3008 : public QObject, private MessageLogger
{
    Q_OBJECT

    public:
        MCP3008(quint8 address);
        void setAddress(quint8 address);
        quint8 getAddress();
        quint16 getData(quint8 channel);

    public slots:

    private:
        quint8 m_address;
        bool initialize();

        char m_txBuffer[3];
        char m_rxBuffer[3];

	private slots:

	signals:


};

#endif // MCP3008_H
