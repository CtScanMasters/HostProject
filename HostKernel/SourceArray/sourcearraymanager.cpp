#include "sourcearraymanager.h"
#include <QDebug>

SourceArrayManager::SourceArrayManager()
{  
    enableLogging(true);
    setName("SourceArrayManager: ");
    logMessage(MSG_INFO, "build");

    m_numberOfArrays = 8;

    for(int i = 0; i < m_numberOfArrays; i ++)
    {
        m_sourceArrayList.append(new SourceArray(i));
    }
}

void SourceArrayManager::setSource(quint8 address, quint8 sensorMask)
{
    m_sourceArrayList.at(address)->setChannel(sensorMask);
}

quint8 SourceArrayManager::getSource(quint8 address)
{
    return m_sourceArrayList.at(address)->getChannel();
}


