#-------------------------------------------------
#
# Project created by QtCreator 2015-12-21T10:20:57
#
#-------------------------------------------------

QT       += core gui
QT += multimediawidgets
QT      +=  webenginewidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        client.cpp \
    login.cpp

HEADERS  += client.h \
    login.h

FORMS    += \
    login.ui
#The resource file must be mentioned in the application.pro file so that qmake knows about it.
#qmake will produce make rules to generate a file called qrc_application.cpp that is linked into the application.
#This file contains all the data for the images and other resources as static C++ arrays of compressed binary data.
RESOURCES += \
    res.qrc
