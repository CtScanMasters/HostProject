#include <QDebug>
#include <stdlib.h>
#include "server.h"

Server::Server(quint16 hostPortNumber)
:   QObject(), SocketHandler()
{
    m_isClientConnected = false;

    m_TcpServer = new QTcpServer(this);

    m_hostPortNumber = hostPortNumber;
    m_myIp = handleRetreiveIpAddress();

    debugMessage("Starting");

    if (!m_TcpServer->listen(QHostAddress::Any, m_hostPortNumber))
    {

        debugMessage(QString("Unable to start: %1.").arg(m_TcpServer->errorString()));

        return;
    }
    else
    {
            debugMessage(QString("SERVER IP: %1 PORT: %2 READY").arg(m_myIp).arg(m_hostPortNumber));
            connect(m_TcpServer, SIGNAL(newConnection()), this, SLOT(newClient()));
    }
}

void Server::newClient()
{
    m_TcpSocketList.append(m_TcpServer->nextPendingConnection());
    connect(m_TcpSocketList.last(), SIGNAL(readyRead()), this, SLOT(readData()));
    connect(m_TcpSocketList.last(), SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(displaySocketState(QAbstractSocket::SocketState)));

    debugMessage(QString("New client is connected: %1 %2 %3").arg(m_TcpSocketList.last()->peerName())
                                    .arg(m_TcpSocketList.last()->peerAddress().toString())
                                        .arg(m_TcpSocketList.last()->peerPort()));

    m_isClientConnected = true;

}

void Server::sendData(QByteArray &byteArray)
{
    if(!m_TcpSocketList.empty())
    {
        for(int i = 0; i < m_TcpSocketList.size(); i++)
        {
            if(m_TcpSocketList.at(i)->state() == QAbstractSocket::UnconnectedState)
            {
                m_TcpSocketList.removeAt(i);
                if(m_TcpSocketList.empty())
                {
                    debugMessage("No hosts connected");
                    m_isClientConnected = false;
                    return;
                }
            }
            handleSendData(m_TcpSocketList.at(i), byteArray);
        }
    }
    else
    {
        debugMessage("No hosts connected");
        m_isClientConnected = false;
        return;
    }
}

void Server::readData()
{
    QTcpSocket* clientSocket = (QTcpSocket *)sender();

    if(handleReceiveData(clientSocket))
    {
        newDataAvailable();
    }
}

void Server::displaySocketState(QAbstractSocket::SocketState socketState)
{
    QTcpSocket *tcpSocket = (QTcpSocket *)sender();

    if(!hanldeSocketState(socketState))
    {
        disconnect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                   this, SLOT(displaySocketState(QAbstractSocket::SocketState)));

    }
}

void Server::newDataAvailable()
{
    emit newDataAvailableSignal();
}

bool Server::isClientConnected()
{
    return m_isClientConnected;
}




