#include "kernel.h"
#include <QDebug>

Kernel::Kernel()
{
    enableLogging(true);
    setName("Kernel: ");
    logMessage(MSG_INFO, "build");

}

void Kernel::heartbeat()
{
    logMessage(MSG_INFO, "heartbeat");
}


void Kernel::start()
{
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(heartbeat()));
    m_timer.start(2000);

    m_scanControl = new ScanControl(this);
}

