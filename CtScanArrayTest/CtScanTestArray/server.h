#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork>
#include <QTimer>
#include <QAbstractSocket>
#include "sockethandler.h"

class Server : public QObject, public SocketHandler
{
    Q_OBJECT

public:
    Server(quint16 hostPortNumber);
    void sendData(QByteArray byteArray);
    bool isClientConnected();

private slots:    
    void newClient();
    void readData();
    void displaySocketState(QAbstractSocket::SocketState socketState);


signals:
    void newDataReceivedSignal();


private:       
    void newDataAvailable();

    QTcpServer *m_TcpServer;
    QList<QTcpSocket* > m_TcpSocketList;
    QString m_myIp;
    quint16 m_hostPortNumber;
    QList<QByteArray> m_DataBufferInList;
    QHostAddress m_clientHostAddress;
    bool m_isClientConnected;

signals:
    void newDataAvailableSignal();

};

#endif //SERVER_H
