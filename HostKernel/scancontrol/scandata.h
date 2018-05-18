#ifndef SCANDATA_H
#define SCANDATA_H

#include <QObject>

class ScanData : public QObject
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
        quint16 m_scanNumber;
        QByteArray m_scanDataArray;
		
	private slots:

	signals:


};

#endif // SCANDATA_H
