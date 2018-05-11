#include "messagelogger.h"
#include <QDebug>

MessageLogger::MessageLogger()
{
    enableLogging(true);
}

MessageLogger::MessageLogger(QString logname)
{
    enableLogging(true);
    setName(logname);
}

void MessageLogger::enableLogging(bool enable)
{
    m_loggingIsEnabled = enable;
}

void MessageLogger::setName(QString logname)
{
    m_logname = logname;
}

QString MessageLogger::getName()
{
    return m_logname;
}

void MessageLogger::logMessage(messageType type, QString message)
{
    QString logMessage;
    logMessage.append(m_logname);
    logMessage.append(message);

    switch(type)
    {
        case MSG_DEBUG:     qDebug() << logMessage;
        break;
        case MSG_WARNING:   qWarning() << logMessage;
        break;
        case MSG_CRITICAL:  qCritical() << logMessage;
        break;
        case MSG_INFO:      qInfo() << logMessage;
        break;
    }

}
