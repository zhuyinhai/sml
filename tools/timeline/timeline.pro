#-------------------------------------------------
#
# Project created by QtCreator 2015-09-21T20:51:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = timeline
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    timelinedelegate.cpp \
    timelineitem.cpp \
    timelineeditor.cpp \
    keyframelist.cpp \
    timelineview.cpp \
    layer.cpp

HEADERS  += mainwindow.h \
    timelinedelegate.h \
    timelineitem.h \
    timelineeditor.h \
    keyframelist.h \
    timelineview.h \
    layer.h \
    singleton.h \
    call_once.h

FORMS    += mainwindow.ui
