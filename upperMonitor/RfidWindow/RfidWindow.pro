#-------------------------------------------------
#
# Project created by QtCreator 2016-11-05T17:44:54
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RfidWindow
TEMPLATE = app


SOURCES += main.cpp\
        rfidmainwindow.cpp \
    rfidoperating.cpp

HEADERS  += rfidmainwindow.h \
    rfidoperating.h

FORMS    += rfidmainwindow.ui
