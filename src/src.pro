TARGET = woptimizer
INCLUDEPATH += $$PWD

QT += \
    widgets

HEADERS += $$PWD/*.h
SOURCES += $$PWD/*.cpp

CONFIG(debug, debug|release) {
    message("Debug Build !")
    win32 {
        # Windows debug
        CONFIG += console
    }
} else {
    message("Release Build !")
}
