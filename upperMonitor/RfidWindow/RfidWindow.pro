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
RC_FILE = logo/logo.rc


SOURCES += main.cpp \
    Controller/connectionservice.cpp \
    Model/rfidoperating.cpp \
    View/rfidmainwindow.cpp \
    Controller/connectionserviceerror.cpp \
    Controller/commodity.cpp \
    Controller/qconnectionthread.cpp \
    View/login.cpp \
    View/widgeterror.cpp \
    Model/rfidopreatingmachine.cpp \
    Model/opreatingthread.cpp \
    Model/rfidcardreadinfo.cpp \
    Controller/configureinfo.cpp \
    View/queryresult.cpp \
    View/administratormainwindow.cpp

HEADERS  += \
    Controller/connectionservice.h \
    Model/rfidoperating.h \
    View/rfidmainwindow.h \
    Controller/connectionserviceerror.h \
    Controller/commodity.h \
    Controller/qconnectionthread.h \
    View/login.h \
    View/widgeterror.h \
    Model/rfidopreatingmachine.h \
    Model/opreatingthread.h \
    Model/rfidcardreadinfo.h \
    Controller/configureinfo.h \
    View/queryresult.h \
    View/administratormainwindow.h

FORMS    += \
    View/rfidmainwindow.ui \
    View/login.ui \
    View/queryresult.ui \
    View/administratormainwindow.ui

DISTFILES += \
    logo/logo.ico \
    logo/logo.rc
