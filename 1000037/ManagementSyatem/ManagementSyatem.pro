#-------------------------------------------------
#
# Project created by QtCreator 2019-08-03T10:02:45
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ManagementSyatem
TEMPLATE = app

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
        main.cpp \
        widget.cpp \
    landwidget.cpp \
    enter.cpp \
    browse.cpp \
    sort.cpp \
    admin.cpp \
    database.cpp

HEADERS += \
        widget.h \
    landwidget.h \
    enter.h \
    browse.h \
    sort.h \
    admin.h \
    database.h

FORMS += \
        widget.ui \
    landwidget.ui \
    enter.ui \
    browse.ui \
    sort.ui \
    admin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    exe.qrc

DISTFILES += \
    exe.rc
RC_FILE += exe.rc
