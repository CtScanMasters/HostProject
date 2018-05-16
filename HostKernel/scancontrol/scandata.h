#ifndef SCANDATA_H
#define SCANDATA_H

#include <QObject>

class ScanData : public QObject
{
    Q_OBJECT

    public:
        ScanData();
        void addData(quint16 scanNumber, quint16 arrayAddress, quint16 sourceNumber, QByteArray byteArray);

    public slots:

    private:
        QByteArray m_scanDataArray;
		
	private slots:

	signals:


};

#endif // SCANDATA_H
