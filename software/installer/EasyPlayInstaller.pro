QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

### CONFIG
CONFIG += c++17

QMAKE_LFLAGS_WINDOWS += /MANIFESTUAC:level=\'requireAdministrator\'

### SOURCE FILES
INCLUDEPATH += src/

SOURCES += \
    src/artifactshandler.cpp \
    src/firefoxhandler.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    src/artifactshandler.h \
    src/firefoxhandler.h \
    src/mainwindow.h

FORMS += \
    forms/mainwindow.ui

### BUILD
DESTDIR = $$PWD/build

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
