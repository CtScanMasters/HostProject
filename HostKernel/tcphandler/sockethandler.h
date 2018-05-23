#ifndef SOCKETHANDLER_H
#define SOCKETHANDLER_H

#include <QTcpSocket>
#include <QMutex>

#include "messagelogger/messagelogger.h"


class SocketHandler : protected MessageLogger
{

private:
    QList<QByteArray> m_dataInBufferList;
    QMutex m_mutex;

protected:
    QString handleRetreiveIpAddress();
    quint64 handleSendData(QTcpSocket *tcpSocket, QByteArray &byteArray);
    bool handleReceiveData(QTcpSocket *tcpSocket);
    bool hanldeSocketState(QAbstractSocket::SocketState socketState);
    void debugMessage(QString message);


public:
    SocketHandler();
    void getReceivedData(QByteArray &byteArray);


};

#endif // SOCKETHANDLER_H
