#ifndef KERNEL_H
#define KERNEL_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include "messagelogger/messagelogger.h"
#include "hardwarecontrol/bcm2835.h"
#include "scancontrol/scancontrol.h"
#include "tcphandler/server.h"


class Kernel : public QObject, private MessageLogger
{
    Q_OBJECT

    public:
        Kernel();

    public slots:


    private:
        QTimer m_heartBeatTimer;
        QTimer m_scanTimer;
        ScanControl *m_scanControl;
        Server *m_server;
        quint16 m_hostPortNumber;
        bool m_hardwareInitialized;

        quint32 m_arrayOffset;
        quint16 m_numberOfScans;
        quint32 m_scanCounter;
        quint32 m_sendCounter;

        bool m_iAmReady;
        bool m_isScanStopped;

        QByteArray m_bufferIn;
        QByteArray m_bufferOut;

        QTime m_time;

        QList<ScanData* > m_scanDataList;

        bool initializeHardwareControl();
        void scanStart();
        void scanStop();
        void getScanData();
        void sendReady();
        void sendNotReady();
        void newScanData();
        void dataDelivery();
        void dataEnd();

		
	private slots:
        void makeScan();
        void readTcpData();
        void writeTcpData();
        void setScanProgress();
        void commandHandler(quint8 command);

	signals:


};

#endif // KERNEL_H
