#-------------------------------------------------
#
# Project created by QtCreator 2015-06-25T02:39:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShowOff
TEMPLATE = app


SOURCES += main.cpp\
    myeventreceiver.cpp \
    CBatchingMesh.cpp

HEADERS  += \
    myeventreceiver.h \
    TileMesh.h \
    WaterTileMesh.h \
    MyShaderCallBack.h \
    TileEdgeMesh.h \
    TileCornerMesh.h \
    DGameMap.h \
    GameManager.h \
    CBatchingMesh.h \
    PathFinding.h \
    DRandom.h

FORMS    +=

INCLUDEPATH += D:\Qt\irrlicht-1.8.1\include\

LIBS += D:\Qt\irrlicht-1.8.1\lib\Win32-gcc\libIrrlicht.a
DEF_FILE += D:\Qt\irrlicht-1.8.1\lib\Win32-gcc\libIrrlicht.def

