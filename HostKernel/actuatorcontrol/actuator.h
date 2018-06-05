#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <QObject>

class Actuator : public QObject
{
    Q_OBJECT

    public:
        Actuator();
        void initialize(quint8 stepPin, quint8 directionPin, quint8 switchPin);
        void moveToPosition(long position);
        void setOffset(long offset);
        void setLimit(long limit);
        void setDirection(bool direction);
        void setSpeed(quint32 speed);
        void setPosition(long position);
        void setSetpointPosition(long position);
        void makeStep();
        void step();

        long getPosition();
        long getSetPointPosition();
        bool getDirection();
        quint16 getSpeed();
        bool isHomed();
        bool atHomeSwitch();

    public slots:


    private:
        long m_position;
        long m_setPointPosition;
        long m_offset;
        long m_limit;
        quint16 m_speed;
        bool m_direction;
        bool m_isHomed;
        bool m_atHomeSwitch;
        bool m_stepPinLevel;

        quint8 m_stepPin;
        quint8 m_directionPin;
        quint8 m_switchPin;

		
	private slots:

	signals:
        void positionChangedSignal(long);
        void actuatorHomedSignal();


};

#endif // ACTUATOR_H
