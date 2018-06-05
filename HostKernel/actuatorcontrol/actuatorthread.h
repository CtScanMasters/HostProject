#ifndef ACTUATORTHREAD_H
#define ACTUATORTHREAD_H

#include <QObject>
#include "actuator.h"

class ActuatorThread : public QObject
{
    Q_OBJECT

public:
    ActuatorThread(Actuator *actuator);

public slots:
    void doActuatorMove();

private:
    Actuator *m_actuator;

signals:
    void readyActuatorMove();

};

#endif // ACTUATORTHREAD_H
