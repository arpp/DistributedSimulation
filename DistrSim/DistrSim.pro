#-------------------------------------------------
#
# Project created by QtCreator 2015-03-28T08:17:29
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
    nodeabstract.cpp \
    edgeabstract.cpp \
    eventabstract.cpp \
    mnode.cpp \
    node.cpp \
    edge.cpp

HEADERS += \
    nodeabstract.h \
    edgeabstract.h \
    eventabstract.h \
    mnode.h \
    node.h \
    edge.h
