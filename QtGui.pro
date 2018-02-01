#-------------------------------------------------
#
# Project created by QtCreator 2018-01-30T21:20:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtGui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        MyPainter.cpp\
        geometry.cpp\
        model.cpp

HEADERS  += mainwindow.h\
        MyPainter.h\
        geometry.h\
        model.h\
        Matrix3x3.h

FORMS    += mainwindow.ui
