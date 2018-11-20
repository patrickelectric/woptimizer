TEMPLATE = lib
CONFIG += plugin
#CONFIG += shared

INCLUDEPATH += \
    $$PWD \
    $$PWD/../../

HEADERS += \
    $$PWD/../../AlgorithmInterface.h \
    $$PWD/*.h \

SOURCES += \
    $$PWD/../../AlgorithmInterface.cpp \
    $$PWD/*.cpp \

DESTDIR = ..
