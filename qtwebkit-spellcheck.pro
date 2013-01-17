isEqual(QT_MAJOR_VERSION, 5) {
    QT += widgets
} else {
    QT += core gui
}

# Create bin directory first on Mac / Linux
mac|unix: system(test -d bin || mkdir bin)

TARGET = spellcheck
TEMPLATE = lib
CONFIG += plugin

LIBS += -lhunspell

DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build
UI_DIR = build

SOURCES += src/spellplugin.cpp \
    src/spellcheck.cpp \
    src/speller.cpp

HEADERS += src/spellplugin.h \
    src/qwebkitplatformplugin.h \
    src/spellcheck.h \
    src/speller.h

!mac:unix {
    target.path = $$[QT_INSTALL_PLUGINS]/webkit
    INSTALLS += target
}
