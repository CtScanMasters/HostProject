#include "sockethandler.h"
#include <QtNetwork>

SocketHandler::SocketHandler()
{

}

QString SocketHandler::handleRetreiveIpAddress()
{
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    return(ipAddress);
}

quint64 SocketHandler::handleSendData(QTcpSocket *tcpSocket, QByteArray &byteArray)
{
    QByteArray block;
    QDataStream dataStreamOut(&block, QIODevice::WriteOnly);
    dataStreamOut.setVersion(QDataStream::Qt_4_0);

    dataStreamOut << byteArray;

    quint64 sendDataSize = tcpSocket->write(block);

    debugMessage(QString("Send: %1 bytes to %2")
                 .arg(sendDataSize).arg(tcpSocket->peerAddress().toString()));

    return sendDataSize;
}

bool SocketHandler::handleReceiveData(QTcpSocket *tcpSocket)
{
        QDataStream m_dataStreamIn;
        m_dataStreamIn.setDevice(tcpSocket);
        m_dataStreamIn.setVersion(QDataStream::Qt_4_0);

        m_dataStreamIn.startTransaction();

        QByteArray byteArray;
        m_dataStreamIn >> byteArray;                

        if(!m_dataStreamIn.commitTransaction())
        {
               debugMessage("Read FAILED");
               return(false);
        }
        else
        {
            m_mutex.lock();
            if(m_dataInBufferList.size() > 10)
            {
                debugMessage("Receive buffer overflow");
                m_dataInBufferList.removeLast();
            }
            m_dataInBufferList.prepend(byteArray);
            m_mutex.unlock();

            debugMessage(QString("Received bytes: %1 from %2")
                         .arg(byteArray.size()).arg(tcpSocket->peerAddress().toString()));
            return(true);
        }
}

void SocketHandler::getReceivedData(QByteArray &byteArray)
{
    if(m_dataInBufferList.size() > 0)
    {
        byteArray = m_dataInBufferList.last();

        m_mutex.lock();
        m_dataInBufferList.removeLast();
        m_mutex.unlock();
    }
    else
    {
        debugMessage("Receive buffer is empty");
    }

}

bool SocketHandler::hanldeSocketState(QAbstractSocket::SocketState socketState)
{
    QString socketStateString;
    socketStateString.append("state: ");

    bool isReady = false;

    switch (socketState)
    {
    case QAbstractSocket::UnconnectedState:
        socketStateString.append("disconnected");
        break;
    case QAbstractSocket::HostLookupState:
        socketStateString.append("lookup state");
        break;
    case QAbstractSocket::ConnectingState:
    {
        socketStateString.append("connecting");
        break;
    }
    case QAbstractSocket::ConnectedState:
        socketStateString.append("connected");
        isReady = true;
        break;
    case QAbstractSocket::BoundState:
        socketStateString.append("bounding");
        break;
    case QAbstractSocket::ClosingState:
        socketStateString.append("closing");
        break;
    case QAbstractSocket::ListeningState:
        socketStateString.append("listening");
        break;
    default:
        socketStateString.append("unknown");
    }

    debugMessage(socketStateString);
    return isReady;
}
void SocketHandler::debugMessage(QString message)
{
    qDebug() << message;
}
