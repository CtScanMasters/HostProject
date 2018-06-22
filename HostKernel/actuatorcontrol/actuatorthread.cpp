#include "actuatorthread.h"
#include <QDebug>
#include <QThread>
#include "hardwarecontrol/bcm2835.h"

ActuatorThread::ActuatorThread(Actuator *actuator)
    :m_actuator(actuator)
{
    qDebug() << Q_FUNC_INFO;
}

void ActuatorThread::doActuatorMove()
{
//    qDebug() << Q_FUNC_INFO;

    long position = 0;
    while(m_actuator->getPosition() != m_actuator->getSetPointPosition())
    {
        m_actuator->makeStep();
//        QThread::msleep(m_actuator->getSpeed());
        bcm2835_delay(1);
    }

    emit readyActuatorMove();

}
