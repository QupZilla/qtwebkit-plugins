isEqual(QT_MAJOR_VERSION, 5) {
    QT *= widgets
} else {
    QT *= core gui
}

TARGET = $$qtLibraryTarget(qtwebkitplugins)
TEMPLATE = lib
CONFIG += plugin

DESTDIR = $$PWD/../bin
OBJECTS_DIR = $$PWD/../build
MOC_DIR = $$PWD/../build
RCC_DIR = $$PWD/../build
UI_DIR = $$PWD/../build

SOURCES += $$PWD/plugin.cpp
HEADERS += $$[QT_INSTALL_HEADERS]/QtWebKit/qwebkitplatformplugin.h \
    plugin.h

include($$PWD/spellcheck/spellcheck.pri)
include($$PWD/notifications/notifications.pri)

!mac:unix {
    target.path = $$[QT_INSTALL_PLUGINS]/webkit
    INSTALLS += target
}
