lessThan(QT_VERSION, 4.8) {
    error("qtwebkit-plugins requires at least Qt 4.8 and QtWebKit 2.3!")
}

TEMPLATE = subdirs
SUBDIRS = src
