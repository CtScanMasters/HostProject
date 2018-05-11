#ifndef MCP3008_H
#define MCP3008_H

#include <QObject>
#include <MessageLogger/messageLogger.h>

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
        void setChannel(quint8 channel);

	private slots:

	signals:


};

#endif // MCP3008_H
