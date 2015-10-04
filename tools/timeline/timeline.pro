#-------------------------------------------------
#
# Project created by QtCreator 2015-09-21T20:51:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = timeline
TEMPLATE = app

#vld_dir = "C:\Program Files (x86)\Visual Leak Detector"
#INCLUDEPATH += $${vld_dir}"\include"
#LIBS += $${vld_dir}"\lib\Win64\vld.lib"

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    timelinedelegate.cpp \
    timelineitem.cpp \
    timelineeditor.cpp \
    keyframelist.cpp \
    timelineview.cpp

HEADERS  += mainwindow.h \
    timelinedelegate.h \
    timelineitem.h \
    timelineeditor.h \
    keyframelist.h \
    timelineview.h

FORMS    += mainwindow.ui
