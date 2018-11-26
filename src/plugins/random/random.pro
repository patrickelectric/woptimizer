TEMPLATE = lib
CONFIG += plugin \
    c++14 \

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
