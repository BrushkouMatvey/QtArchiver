#-------------------------------------------------
#
# Project created by QtCreator 2019-03-24T22:13:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtArchiver
TEMPLATE = app

#Include the interface

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/add_window.cpp \
        src/extract_window.cpp \
    src/lzw.cpp \
    src/huffman.cpp \
    src/rle.cpp

HEADERS += \
        src/mainwindow.h \
        src/add_window.h \
        src/extract_window.h \
    src/lzw.h \
    src/huffman.h \
    src/rle.h \
    src/huffmantreenode.h

FORMS += \
        ui/mainwindow.ui \
        ui/add_window.ui \
        ui/extract_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
        resources.qrc
