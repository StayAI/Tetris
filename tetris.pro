#-------------------------------------------------
#
# Project created by QtCreator 2017-11-17T17:31:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tetris
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mythread.cpp \
    tetris.cpp

HEADERS  += widget.h \
    MyThread.h \
    tetris.h

FORMS    += widget.ui

RESOURCES += \
    image.qrc
