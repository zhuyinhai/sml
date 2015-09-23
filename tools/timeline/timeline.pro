#-------------------------------------------------
#
# Project created by QtCreator 2015-09-21T20:51:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = timeline
TEMPLATE = app

vld_dir = "C:\Program Files (x86)\Visual Leak Detector"
INCLUDEPATH += $${vld_dir}"\include"
LIBS += $${vld_dir}"\lib\Win64\vld.lib"

SOURCES += main.cpp\
        mainwindow.cpp \
    timelinedelegate.cpp \
    timelineitem.cpp

HEADERS  += mainwindow.h \
    timelinedelegate.h \
    timelineitem.h

FORMS    += mainwindow.ui
