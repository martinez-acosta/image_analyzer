#-------------------------------------------------
#
# Project created by QtCreator 2014-01-27T21:07:50
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = OpenImageAnalysis
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    dlgimage.cpp \
    image.cpp \
    imagelabel.cpp \
    imagergb.cpp \
    histogram.cpp \
    qcustomplot.cpp \
    mask.cpp

HEADERS  += \
    mainwindow.h \
    dlgimage.h \
    image.h \
    imagelabel.h \
    imagergb.h \
    histogram.h \
    qcustomplot.h \
    mask.h

FORMS    += \
    mainwindow.ui \
    dlgimage.ui \
    histogram.ui \
    mask.ui

OTHER_FILES +=
