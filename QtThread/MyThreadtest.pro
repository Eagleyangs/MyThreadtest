#-------------------------------------------------
#
# Project created by QtCreator 2019-09-30T11:33:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyThreadtest
TEMPLATE = app


SOURCES += main.cpp\
        Widget.cpp \
    MyThread.cpp

HEADERS  += Widget.h \
    MyThread.h

FORMS    += Widget.ui
