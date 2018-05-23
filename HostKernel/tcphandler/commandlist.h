#ifndef COMMANDLIST_H
#define COMMANDLIST_H

enum commands
{
    COMMAND_SCAN_START,
    COMMAND_SCAN_STOP,
    COMMAND_SCAN_SET_PROGRESS,
    COMMAND_SCAN_GET_DATA,
    COMMAND_SCAN_NEW_DATA,
    COMMAND_SCAN_DATA_DELIVERY,
    COMMAND_SCAN_DATA_END,
    COMMAND_ACTUATOR_FORWARD,
    COMMAND_ACTUATOR_BACKWARD,
    COMMAND_ACTUATOR_POSITION,
    COMMAND_ACTUATOR_HOME,
    COMMAND_SENSOR_VALUE,
    COMMAND_SOURCE_VALUE,
    COMMAND_READY,
    COMMAND_NOT_READY,
};

#endif // COMMANDLIST_H

