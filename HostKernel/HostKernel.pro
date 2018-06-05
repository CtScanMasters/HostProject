QT += core
QT -= gui
QT += network

CONFIG += c++11

TARGET = HostKernel
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    hardwarecontrol/chipselectmanager.cpp \
    hardwarecontrol/MCP23S09.cpp \
    hardwarecontrol/MCP3008.cpp \
    hardwarecontrol/multiplexer.cpp \
    messagelogger/messagelogger.cpp \
    sensorarray/sensorarray.cpp \
    sensorarray/sensorarraymanager.cpp \
    sourcearray/sourcearray.cpp \
    sourcearray/sourcearraymanager.cpp \
    hardwarecontrol/bcm2835.c \
    kernel.cpp \
    scancontrol/scancontrol.cpp \
    scancontrol/scandata.cpp \
    tcphandler/server.cpp \
    tcphandler/sockethandler.cpp \
    actuatorcontrol/actuator.cpp \
    actuatorcontrol/actuatorcontroller.cpp \
    actuatorcontrol/actuatorthread.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    hardwarecontrol/MCP23S09.h \
    hardwarecontrol/MCP3008.h \
    hardwarecontrol/multiplexer.h \
    messagelogger/messagelogger.h \
    sensorarray/sensorarray.h \
    sensorarray/sensorarraymanager.h \
    sourcearray/sourcearray.h \
    sourcearray/sourcearraymanager.h \
    hardwarecontrol/bcm2835.h \
    kernel.h \
    hardwarecontrol/chipselectmanager.h \
    scancontrol/scancontrol.h \
    scancontrol/scandata.h \
    tcphandler/server.h \
    tcphandler/sockethandler.h \
    tcphandler/commandlist.h \
    actuatorcontrol/actuator.h \
    actuatorcontrol/actuatorcontroller.h \
    actuatorcontrol/actuatorthread.h
