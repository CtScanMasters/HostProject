#include "actuator.h"
#include <QDebug>
#include <QThread>
#include "hardwarecontrol/bcm2835.h"

Actuator::Actuator()
{
    setPosition(0);
}

void Actuator::initialize(quint8 stepPin, quint8 directionPin, quint8 switchPin)
{
    m_stepPin = stepPin;
    m_directionPin = directionPin;
    m_switchPin = switchPin;
    m_stepPinLevel = false;
    m_direction = false;
    m_isHomed = false;
    m_atHomeSwitch = false;
    m_speed = 400;

    bcm2835_gpio_fsel(m_stepPin, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(m_directionPin, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(m_switchPin, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_write(m_stepPin, m_stepPinLevel);
    bcm2835_gpio_write(m_directionPin, m_direction);
}

void Actuator::setOffset(long offset)
{
    m_offset = offset;
}

void Actuator::setLimit(long limit)
{
    m_limit = limit;
}

void Actuator::setDirection(bool direction)
{
    m_direction = direction;
    bcm2835_gpio_write(m_directionPin, m_direction);
}

void Actuator::setSpeed(quint32 speed)
{
    m_speed = speed;
}

long Actuator::getPosition()
{
    return(m_position);
}

bool Actuator::getDirection()
{
    return(m_direction);
}

quint16 Actuator::getSpeed()
{
    return(m_speed);
}

bool Actuator::isHomed()
{
    return(m_isHomed);
}

bool Actuator::atHomeSwitch()
{
   //Check switch here
    if(bcm2835_gpio_lev(m_switchPin))
    {
        m_atHomeSwitch = true;
    }
    else
    {
        m_atHomeSwitch = false;
    }
    return m_atHomeSwitch;
}

void Actuator::makeStep()
{
    if(m_direction)
    {
        //Make step
        step();
        setPosition(getPosition() + 1);
    }
    else
    {
        if(atHomeSwitch())
        {
            //Make step
            step();
            setPosition(getPosition() - 1);
        }
        else
        {
            //Home switch reached
            m_isHomed = true;
            setPosition(0);
            setSetpointPosition(0);
            qDebug() << "Actuator::postition: " << "HOMED";
            emit actuatorHomedSignal();
        }
    }

//    qDebug() << "Actuator::postition: " << m_position;
//    bcm2835_gpio_write(m_stepPin, m_stepPinLevel);
}

void Actuator::step()
{
    m_stepPinLevel = true;
    bcm2835_gpio_write(m_stepPin, m_stepPinLevel);
    QThread::usleep(1);
    m_stepPinLevel = false;
    bcm2835_gpio_write(m_stepPin, m_stepPinLevel);
}

void Actuator::setPosition(long position)
{
    m_position = position;
    emit positionChangedSignal(m_position);
}

void Actuator::setSetpointPosition(long position)
{
    m_setPointPosition = position;
}

long Actuator::getSetPointPosition()
{
    return m_setPointPosition;
}
