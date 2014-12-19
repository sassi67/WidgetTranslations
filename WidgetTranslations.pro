#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T09:04:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WidgetTranslations
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    aboutwindow.cpp

HEADERS  += mainwindow.h \
    aboutwindow.h

FORMS    += mainwindow.ui \
    aboutwindow.ui

TRANSLATIONS += tr_de.ts \
                tr_en.ts \
                tr_es.ts \
                tr_it.ts
