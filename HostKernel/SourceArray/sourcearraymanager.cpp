#include "sourcearraymanager.h"
#include <QDebug>

SourceArrayManager::SourceArrayManager(ChipSelectManager *chipSelectManager)
    : m_chipSelectManager(chipSelectManager)
{      
    setName("SourceArrayManager: ");
    logMessage(MSG_INFO, "build");
    enableLogging(true);

    m_numberOfArrays = 8;

    for(int i = 0; i < m_numberOfArrays; i ++)
    {
        m_sourceArrayList.append(new SourceArray(i));
    }
}

void SourceArrayManager::setSource(quint8 address, quint8 sourceChannel)
{
    m_chipSelectManager->setChipSelect(address);


    logMessage(MSG_INFO, QString("setSource: %1").arg(sourceChannel));

    m_sourceArrayList.at(address)->setChannel(sourceChannel);
}

void SourceArrayManager::clearSource(quint8 address)
{
    m_chipSelectManager->setChipSelect(address);
    m_sourceArrayList.at(address)->clearChannels();
    m_sourceArrayList.at(address)->initialize();
}

quint8 SourceArrayManager::getSource(quint8 address)
{
    return m_sourceArrayList.at(address)->getChannel();
}

void SourceArrayManager::initialize()
{
    for(quint8 i = 0; i < m_numberOfArrays; i++)
    {
        m_chipSelectManager->setChipSelect(i);

        logMessage(MSG_INFO, QString("initialize array: %1").arg(i));

        m_sourceArrayList.at(i)->initialize();
    }
}
