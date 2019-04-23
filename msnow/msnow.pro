#-------------------------------------------------
#
# Project created by QtCreator 2018-09-17T11:26:56
#
#-------------------------------------------------

QT       += core gui

RC_ICONS = snow.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = msnow
TEMPLATE = app


SOURCES += main.cpp\
        test.cpp \
    about.cpp

HEADERS  += test.h \
    about.h

FORMS    += test.ui \
    about.ui

RESOURCES += \
    res.qrc
