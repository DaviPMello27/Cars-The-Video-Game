TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        src/animations.cpp \
        src/controls.cpp \
        src/menu.cpp \
        src/text.cpp

win32: LIBS += -L$$PWD/../../../SDL/SDL2-2.0.10/x86_64-w64-mingw32/lib/ -lSDL2

INCLUDEPATH += $$PWD/../../../SDL/SDL2-2.0.10/x86_64-w64-mingw32/include
DEPENDPATH += $$PWD/../../../SDL/SDL2-2.0.10/x86_64-w64-mingw32/include

win32: LIBS += -L$$PWD/../../../SDL/SDL2_image-2.0.5/x86_64-w64-mingw32/lib/ -lSDL2_image

INCLUDEPATH += $$PWD/../../../SDL/SDL2_image-2.0.5/x86_64-w64-mingw32/include
DEPENDPATH += $$PWD/../../../SDL/SDL2_image-2.0.5/x86_64-w64-mingw32/include

HEADERS += header/animations.h \
    header/controls.h \
    header/menu.h \
    header/text.h
HEADERS += header/structs.h

INCLUDEPATH += header
