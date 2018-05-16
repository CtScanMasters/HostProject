#ifndef SOURCEARRAYMANAGER_H
#define SOURCEARRAYMANAGER_H

#include <QObject>
#include <QList>
#include "messagelogger/messagelogger.h"
#include "sourcearray.h"
#include "hardwarecontrol/chipselectmanager.h"

class SourceArrayManager : public QObject, private MessageLogger
{
    Q_OBJECT

    public:
        SourceArrayManager(ChipSelectManager *chipSelectManager);
        void setSource(quint8 address, quint8 sourceMask);
        quint8 getSource(quint8 address);
        void initialize();

    public slots:

    private:
        QList<SourceArray *> m_sourceArrayList;
        quint8 m_numberOfArrays;
        ChipSelectManager *m_chipSelectManager;
		
	private slots:

	signals:


};

#endif // SOURCEARRAYMANAGER_H
