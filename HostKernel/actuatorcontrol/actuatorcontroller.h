#ifndef ACTUATORCONTROLLER_H
#define ACTUATORCONTROLLER_H

#include <QObject>
#include <QThread>

#include "actuatorthread.h"
#include "actuator.h"

class ActuatorController : public QObject
{
    Q_OBJECT
    QThread m_workerThread;

    public:
        ActuatorController();
        ~ActuatorController();

    public slots:
        void moveActuatorForward();
        void moveActuatorBackward();
        void stopActuatorMovement();
        void homeActuator();
        void moveActuatorTo();
        void setSetpointPosition(long position);
        void actuatorHomed();
        void setSpeed(quint32 speed);
        long getPosition();

    private:        
        ActuatorThread *m_actuatorThread;
        Actuator *m_actuator;
        bool m_actuatorStop;
        bool m_moveForward;
        bool m_moveBackward;
        long m_setPointPosition;

		
	private slots:
        void handleActuatorReady();
        void positionChanged(long);



	signals:
        void startOperation();
        void positionChangedSignal(long);
        void actuatorHomedSignal();
        void actuatorReadySignal();


};

#endif // ACTUATORCONTROLLER_H
