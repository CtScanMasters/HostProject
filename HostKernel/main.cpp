#include <QCoreApplication>

#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

#include "HardwareControl/MCP3008.h"
#include "HardwareControl/MCP23S09.h"
#include "HardwareControl/multiplexer.h"
#include "HardwareControl/chipslelectmanager.h"
#include "SensorArray/sensorarraymanager.h"

// Smart pointer to log file
QScopedPointer<QFile>   m_logFile;

void msgHandler(QtMsgType type, const QMessageLogContext &, const QString & str)
{
    QString messageString;

    QDateTime dateTime;
    dateTime = QDateTime::currentDateTime();

    messageString.append(dateTime.toString("yyyy-MM-dd hh:mm:ss:zzz"));
    messageString.append("  ");

    switch (type) {
    case QtDebugMsg:
        messageString.append(QString("DEBUG : %1").arg(str));
        break;
    case QtWarningMsg:
        messageString.append(QString("WARNING : %1").arg(str));
        break;
    case QtCriticalMsg:
        messageString.append(QString("CRITICAL : %1").arg(str));
        break;
    case QtInfoMsg:
        messageString.append(QString("INFO : %1").arg(str));
        break;
    case QtFatalMsg:
        messageString.append(QString("FATAL : %1").arg(str));
        abort();
    }

    QTextStream out(m_logFile.data());
    out << messageString << endl;
    out.flush();

    messageString.append("\n");

    QTextStream consolePrinter(stdout);
    consolePrinter << messageString;

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    m_logFile.reset(new QFile("SCANLOG.log"));
    m_logFile.data()->open(QFile::WriteOnly|QFile::Truncate);
    m_logFile.data()->close();
    m_logFile.data()->open(QFile::Append | QFile::Text);
    qInstallMessageHandler(msgHandler);

    qInfo() << "------------START CT SCANMASTER KERNEL V1.0 2018 by CT ScanMasters-------------";

    SensorArrayManager manager(10);

    return a.exec();
}
