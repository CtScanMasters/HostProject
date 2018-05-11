QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    HardwareControl/MCP23S09.cpp \
    HardwareControl/MCP3008.cpp \
    SensorArray/sensorarray.cpp \
    SensorArray/sensorarraymanager.cpp \
    SensorArray/sensordata.cpp \
    SourceArray/sourcearray.cpp \
    HardwareControl/chipselectmanager.cpp \
    HardwareControl/multiplexer.cpp \
    MessageLogger/messageLogger.cpp \
    SourceArray/sourcearraymanager.cpp

HEADERS += \
    HardwareControl/MCP23S09.h \
    HardwareControl/MCP3008.h \
    SensorArray/sensorarray.h \
    SensorArray/sensorarraymanager.h \
    SensorArray/sensordata.h \
    SourceArray/sourcearray.h \
    HardwareControl/chipslelectmanager.h \
    MessageLogger/messageLogger.h \
    HardwareControl/multiplexer.h \
    SourceArray/sourcearraymanager.h
