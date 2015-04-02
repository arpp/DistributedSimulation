#-------------------------------------------------
#
# Project created by QtCreator 2015-04-02T14:38:56
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = DistrSim
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    edgeabstract.cpp \
    nodeabstract.cpp \
    eventabstract.cpp \
    mnode.cpp \
    eventqueues.cpp \
    eventprocessworker.cpp \
    sendqueueworker.cpp \
    recvqueueworker.cpp

HEADERS += \
    edgeabstract.h \
    nodeabstract.h \
    eventabstract.h \
    mnode.h \
    eventqueues.h \
    eventprocessworker.h \
    sendqueueworker.h \
    recvqueueworker.h
