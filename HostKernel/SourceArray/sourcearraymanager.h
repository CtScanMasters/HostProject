#ifndef SOURCEARRAYMANAGER_H
#define SOURCEARRAYMANAGER_H

#include <QObject>
#include <QList>
#include "messagelogger/messagelogger.h"
#include "sourcearray.h"

class SourceArrayManager : public QObject, private MessageLogger
{
    Q_OBJECT

    public:
        SourceArrayManager();
        void setSource(quint8 address, quint8 sensorMask);
        quint8 getSource(quint8 address);

    public slots:

    private:
        QList<SourceArray *> m_sourceArrayList;
        quint8 m_numberOfArrays;
		
	private slots:

	signals:


};

#endif // SOURCEARRAYMANAGER_H
