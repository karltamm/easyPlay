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
    src/logger.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    src/artifactshandler.h \
    src/firefoxhandler.h \
    src/logger.h \
    src/mainwindow.h

FORMS += \
    forms/mainwindow.ui \
    forms/welcomescreen.ui

### BUILD
DESTDIR = $$PWD/build
ARTIFACTS_SRC_DIR = $$PWD/artifacts

# Driver
DRIVER_PATH = $$ARTIFACTS_SRC_DIR/EasyPlay.exe
driver.depends = $$DRIVER_PATH
driver.target = EasyPlay.exe
driver.commands = $(COPY_DIR) $$system_path($$DRIVER_PATH) $$system_path($$DESTDIR)
QMAKE_EXTRA_TARGETS += driver
PRE_TARGETDEPS += EasyPlay.exe

# Native app manifest
APP_MANIFEST_PATH = $$ARTIFACTS_SRC_DIR/easyplay-native-app-manifest.json
appManifest.depends = $$appManifest_PATH
appManifest.target = easyplay-native-app-manifest.json
appManifest.commands = $(COPY_DIR) $$system_path($$APP_MANIFEST_PATH) $$system_path($$DESTDIR)
QMAKE_EXTRA_TARGETS += appManifest
PRE_TARGETDEPS += easyplay-native-app-manifest.json



qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
