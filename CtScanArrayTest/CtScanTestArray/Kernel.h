#ifndef KERNEL_H
#define KERNEL_H

#include <QObject>
#include <QTimer>

#include "server.h"
#include "mcp3008.h"
#include "mcp23s09.h"

class Kernel : public QObject
{
    Q_OBJECT

public:
    Kernel();


private:
    Server *m_kernelServer;
    QTimer *m_adcInteruptTimer;
    MCP3008 *m_adConverter;
    MCP23S09 *m_ioExpander;
    QList<uint16_t> m_adcValueList;
    quint8 m_ioMask;

    void initializeBCM();

private slots:
    void adcReadSlot();
    void readServerData();





};

#endif // KERNEL_H
