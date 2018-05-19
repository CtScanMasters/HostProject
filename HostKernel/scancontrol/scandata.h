#ifndef SCANDATA_H
#define SCANDATA_H

#include <QObject>
#include "messagelogger/messagelogger.h"

class ScanData : public QObject, private MessageLogger
{
    Q_OBJECT

    public:
        ScanData();
        void setScanNumber(quint16 scanNumber);
        quint16 getScanNumber();
        void addArrayScan(quint16 address, quint16 source);
        void addSensorData(quint16 data);
        QByteArray& getData();

    public slots:

    private:
        QString m_logName;
        quint16 m_scanNumber;
        QByteArray m_scanDataArray;
        void addData(quint16 data);
		
	private slots:

	signals:


};

#endif // SCANDATA_H
