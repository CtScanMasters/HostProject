#ifndef MESSAGELOGGER_H
#define MESSAGELOGGER_H

#include <QString>

class MessageLogger
{
    public:
        MessageLogger();
        MessageLogger(QString logname);

    private:
        QString m_logname;
        bool m_loggingIsEnabled;
		
    protected:
        enum messageType
        {
            MSG_DEBUG,
            MSG_WARNING,
            MSG_CRITICAL,
            MSG_INFO
        };

        void enableLogging(bool enable);
        bool isEnabled();
        void setName(QString logname);
        QString getName();
        void logMessage(messageType messageType, QString message);





};

#endif // MESSAGELOGGER_H
