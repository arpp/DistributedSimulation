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
    createNetwork/client.cpp \
    createNetwork/connections.cpp \
    createNetwork/connector.cpp \
    createNetwork/connecttoall.cpp \
    createNetwork/fileshare.cpp \
    createNetwork/server.cpp \
    readgraph.cpp \
    createNetwork/blockwriter.cpp \
    createNetwork/blockreader.cpp

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
    createNetwork/client.h \
    createNetwork/connections.h \
    createNetwork/connector.h \
    createNetwork/connecttoall.h \
    createNetwork/fileshare.h \
    createNetwork/server.h \
    readgraph.h \
    createNetwork/blockwriter.h \
    createNetwork/blockreader.h
