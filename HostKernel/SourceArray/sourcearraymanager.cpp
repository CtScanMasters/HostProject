#include "sourcearraymanager.h"
#include <QDebug>

SourceArrayManager::SourceArrayManager(ChipSelectManager *chipSelectManager)
    : m_chipSelectManager(chipSelectManager)
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

void SourceArrayManager::setSource(quint8 address, quint8 sourceMask)
{
    logMessage(MSG_INFO, QString("setSource: %1").arg(sourceMask));
    m_chipSelectManager->setChipSelect(address);
    m_sourceArrayList.at(address)->setChannel(sourceMask);
}

quint8 SourceArrayManager::getSource(quint8 address)
{
    return m_sourceArrayList.at(address)->getChannel();
}

void SourceArrayManager::initialize()
{
    for(int i = 0; i < m_sourceArrayList.size(); i++)
    {
        logMessage(MSG_INFO, QString("initialize array: %1").arg(i));
        m_chipSelectManager->setChipSelect(i);
        m_sourceArrayList.at(i)->initialize();
    }
}
