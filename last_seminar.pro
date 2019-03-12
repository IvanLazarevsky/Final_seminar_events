TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    observable.cpp \
    eventbus.cpp \
    sensor.cpp

HEADERS += \
    observable.h \
    eventbus.h \
    events.h \
    sensor.h \
    sensor_data.h
