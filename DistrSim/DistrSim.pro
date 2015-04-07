#-------------------------------------------------
#
# Project created by QtCreator 2015-04-02T14:38:56
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

TARGET = DistrSim
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    edgeabstract.cpp \
    nodeabstract.cpp \
    mnode.cpp \
    eventqueues.cpp \
    eventprocessworker.cpp \
    sendqueueworker.cpp \
    recvqueueworker.cpp \
    examplenode.cpp \
    exampleedge.cpp \
    recvqsocketworker.cpp \
    eventdata.cpp \
    event.cpp \
    createnetwork/client.cpp \
    createnetwork/connections.cpp \
    createnetwork/connector.cpp \
    createnetwork/connecttoall.cpp \
    createnetwork/fileshare.cpp \
    createnetwork/server.cpp

HEADERS += \
    edgeabstract.h \
    nodeabstract.h \
    mnode.h \
    eventqueues.h \
    eventprocessworker.h \
    sendqueueworker.h \
    recvqueueworker.h \
    examplenode.h \
    exampleedge.h \
    recvqsocketworker.h \
    eventdata.h \
    event.h \
    createnetwork/client.h \
    createnetwork/connections.h \
    createnetwork/connector.h \
    createnetwork/connecttoall.h \
    createnetwork/fileshare.h \
    createnetwork/server.h
