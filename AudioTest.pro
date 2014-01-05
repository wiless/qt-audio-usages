#-------------------------------------------------
#
# Project created by QtCreator 2014-01-02T21:33:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += /usr/include/QtMobility /usr/include/QtMultimediaKit
LIBS += -lQtMultimediaKit -lqwt -ggdb

TARGET = AudioTest
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    rawgenerator.cpp

HEADERS  += dialog.h \
    rawgenerator.h

FORMS    += dialog.ui
