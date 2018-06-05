#include "actuatorcontroller.h"
#include <QDebug>
#include "hardwarecontrol/bcm2835.h"

ActuatorController::ActuatorController()
{
    bcm2835_init();

    m_actuatorStop = true;
    m_moveForward = false;
    m_moveBackward = false;

    m_actuator = new Actuator;
    m_actuator->initialize(RPI_V2_GPIO_P1_08, RPI_V2_GPIO_P1_10, RPI_V2_GPIO_P1_12);
    m_actuator->setSpeed(5000);

    m_actuatorThread = new ActuatorThread(m_actuator);
    m_actuatorThread->moveToThread(&m_workerThread);
    connect(&m_workerThread, SIGNAL(finished()), m_actuatorThread, SLOT(deleteLater()));
    connect(this, SIGNAL(startOperation()), m_actuatorThread, SLOT(doActuatorMove()));
    connect(m_actuatorThread, SIGNAL(readyActuatorMove()), this, SLOT(handleActuatorReady()));   
    connect(m_actuator, SIGNAL(positionChangedSignal(long)), this, SLOT(positionChanged(long)));
    connect(m_actuator, SIGNAL(actuatorHomedSignal()), this, SLOT(actuatorHomed()));


    qDebug() << Q_FUNC_INFO;
    m_workerThread.start();
}

ActuatorController::~ActuatorController()
{
    qDebug() << Q_FUNC_INFO;

    m_workerThread.quit();
    m_workerThread.wait();
}

void ActuatorController::handleActuatorReady()
{
    qDebug() << Q_FUNC_INFO;    

    if(m_actuatorStop)
    {
        qDebug() << "Actuator stop";        
    }
    else
    {
        if(m_moveForward)
        {
            moveActuatorForward();
        }
        if(m_moveBackward)
        {
            moveActuatorBackward();
        }
    }

    emit actuatorReadySignal();

}

void ActuatorController::moveActuatorForward()
{
    qDebug() << Q_FUNC_INFO;
    m_moveForward = true;
    m_moveBackward = false;
    m_actuatorStop = false;
    m_actuator->setDirection(true);
    m_actuator->setSetpointPosition(m_actuator->getPosition() + 1);
    emit startOperation();
}

void ActuatorController::moveActuatorBackward()
{
    qDebug() << Q_FUNC_INFO;
    m_moveForward = false;
    m_moveBackward = true;
    m_actuatorStop = false;
    m_actuator->setDirection(false);
    m_actuator->setSetpointPosition(m_actuator->getPosition() - 1);
    emit startOperation();
}

void ActuatorController::stopActuatorMovement()
{
    qDebug() << Q_FUNC_INFO;

    m_actuatorStop = true;
}

void ActuatorController::homeActuator()
{
    qDebug() << Q_FUNC_INFO;

    setSetpointPosition(-999999999);
    moveActuatorTo();
}

void ActuatorController::moveActuatorTo()
{
    qDebug() << Q_FUNC_INFO;
    m_moveForward = false;
    m_moveBackward = false;
    m_actuatorStop = false;

    if(m_setPointPosition > m_actuator->getPosition())
    {
        m_actuator->setDirection(true);
        m_actuator->setSetpointPosition(m_setPointPosition);
        emit startOperation();
    }
    else
    {
        m_actuator->setDirection(false);
        m_actuator->setSetpointPosition(m_setPointPosition);
        emit startOperation();
    }
}

void ActuatorController::setSetpointPosition(long position)
{
    qDebug() << Q_FUNC_INFO;
    m_setPointPosition = position;

}

void ActuatorController::positionChanged(long position)
{
    emit positionChangedSignal(position);
}

void ActuatorController::actuatorHomed()
{
    emit actuatorHomedSignal();
}

void ActuatorController::setSpeed(quint32 speed)
{
    m_actuator->setSpeed(speed);
}

long ActuatorController::getPosition()
{
    return m_actuator->getPosition();
}
