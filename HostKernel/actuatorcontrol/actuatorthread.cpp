#include "actuatorthread.h"
#include <QDebug>
#include <QThread>

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
        QThread::msleep(m_actuator->getSpeed());
    }

    emit readyActuatorMove();

}
