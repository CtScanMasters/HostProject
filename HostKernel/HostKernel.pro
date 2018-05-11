QT += core
QT -= gui

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
    sensorarray/sensordata.cpp \
    sourcearray/sourcearray.cpp \
    sourcearray/sourcearraymanager.cpp \
    hardwarecontrol/bcm2835.c \
    kernel.cpp

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
    hardwarecontrol/chipslelectmanager.h \
    hardwarecontrol/MCP23S09.h \
    hardwarecontrol/MCP3008.h \
    hardwarecontrol/multiplexer.h \
    messagelogger/messagelogger.h \
    sensorarray/sensorarray.h \
    sensorarray/sensorarraymanager.h \
    sensorarray/sensordata.h \
    sourcearray/sourcearray.h \
    sourcearray/sourcearraymanager.h \
    hardwarecontrol/bcm2835.h \
    kernel.h
