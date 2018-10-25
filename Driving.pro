#-------------------------------------------------
#
# Project created by QtCreator 2018-09-05T17:16:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Driving
TEMPLATE = app


SOURCES += main.cpp\
        lanedrive.cpp \
    qlearning.cpp \
    mainwindow.cpp \
    mapdrive.cpp \
    routeplanning.cpp \
    homepage.cpp \
    control.cpp

HEADERS  += lanedrive.h \
    qlearning.h \
    mainwindow.h \
    head.h \
    mapdrive.h \
    routeplanning.h \
    homepage.h \
    control.h

RESOURCES += \
    images.qrc
