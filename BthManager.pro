#-------------------------------------------------
#
# Project created by QtCreator 2017-11-18T13:51:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BthManager
TEMPLATE = app


SOURCES += main.cpp\
        BthWindow.cpp \
    BthDefaultAuthCallback.cpp

HEADERS  += BthWindow.h \
    BthAbstarctClass.h \
    defines.h \
    BthAbstractDevice.h \
    BthRadioModule.h \
    BthManager.h \
    BthPeripheralDevice.h \
    BthPhoneDevice.h \
    BthStandardModel.h

FORMS    += BthWindow.ui

win32:LIBS += -lsetupapi -lkernel32 -lBthprops -lws2_32 -lOle32


