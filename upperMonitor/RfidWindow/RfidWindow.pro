#-------------------------------------------------
#
# Project created by QtCreator 2016-11-05T17:44:54
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RfidWindow
TEMPLATE = app


SOURCES += main.cpp \
    Controller/connectionservice.cpp \
    Model/rfidoperating.cpp \
    View/rfidmainwindow.cpp \
    Controller/connectionserviceerror.cpp

HEADERS  += \
    Controller/connectionservice.h \
    Model/rfidoperating.h \
    View/rfidmainwindow.h \
    Controller/connectionserviceerror.h

FORMS    += \
    View/rfidmainwindow.ui
