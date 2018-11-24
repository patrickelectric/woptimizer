TARGET = woptimizer
INCLUDEPATH += $$PWD

QT += \
    widgets

HEADERS += $$PWD/AlgorithmInterface.h
SOURCES += $$PWD/AlgorithmInterface.cpp

test {
    message(Configuring test build...)
    QT += testlib

    HEADERS += \
        $$PWD/Test.h
    SOURCES += \
        $$PWD/Test.cpp
} else {
    SOURCES += \
        $$PWD/main.cpp

    CONFIG(debug, debug|release) {
    message("Debug Build !")
    win32 {
        # Windows debug
        CONFIG += console
    }
    } else {
        message("Release Build !")
    }
}
