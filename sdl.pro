TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/highscore.cpp \
    src/resolution.cpp
SOURCES += src/animations.cpp
SOURCES += src/controls.cpp
SOURCES += src/menu.cpp
SOURCES += src/text.cpp
SOURCES += src/toi.cpp

win32: LIBS += -L$$PWD/../../../SDL/SDL2-2.0.10/x86_64-w64-mingw32/lib/ -lSDL2

INCLUDEPATH += $$PWD/../../../SDL/SDL2-2.0.10/x86_64-w64-mingw32/include
DEPENDPATH += $$PWD/../../../SDL/SDL2-2.0.10/x86_64-w64-mingw32/include

win32: LIBS += -L$$PWD/../../../SDL/SDL2_image-2.0.5/x86_64-w64-mingw32/lib/ -lSDL2_image

INCLUDEPATH += $$PWD/../../../SDL/SDL2_image-2.0.5/x86_64-w64-mingw32/include
DEPENDPATH += $$PWD/../../../SDL/SDL2_image-2.0.5/x86_64-w64-mingw32/include

HEADERS += header/animations.h \
    header/highscore.h \
    header/resolution.h
HEADERS += header/controls.h
HEADERS += header/menu.h
HEADERS += header/text.h
HEADERS += header/structs.h
HEADERS += header/toi.h

INCLUDEPATH += header

RESOURCES +=
