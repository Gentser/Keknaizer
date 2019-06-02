#-------------------------------------------------
#
# Project created by QtCreator 2019-05-31T21:49:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spitsyn_kurs
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    allocator.cpp \
    manipulator.cpp \
    timelineitem.cpp \
    timeline.cpp \
    ganttchart.cpp \
    exception.cpp

HEADERS += \
        mainwindow.h \
    allocator.h \
    iterator.h \
    manipulator.h \
    singletone.h \
    serializer.h \
    timelineitem.h \
    timeline.h \
    ganttchart.h \
    exception.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    tests.txt
