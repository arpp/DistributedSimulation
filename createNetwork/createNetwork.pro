#-------------------------------------------------
#
# Project created by QtCreator 2015-03-28T10:30:07
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

TARGET = createNetwork
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    server.cpp \
    client.cpp \
    connections.cpp \
    connecttoall.cpp \
    connector.cpp \
    fileshare.cpp

HEADERS += \
    server.h \
    client.h \
    connections.h \
    connecttoall.h \
    connector.h \
    fileshare.h
