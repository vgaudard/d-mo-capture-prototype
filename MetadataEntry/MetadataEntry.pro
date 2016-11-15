#-------------------------------------------------
#
# Project created by QtCreator 2016-11-14T22:19:23
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = MetadataEntry
TEMPLATE = app

QMAKE_CFLAGS +=  -std=c++11
QMAKE_CXXFLAGS +=  -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    metadatadialog.cpp \
    entry.cpp \
    entrylabel.cpp

HEADERS  += mainwindow.h \
    metadatadialog.h \
    entry.h \
    entrylabel.h

FORMS    += mainwindow.ui \
    metadatadialog.ui
