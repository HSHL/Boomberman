# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/GNU_MinGW-Windows-Windows
TARGET = Boomberman
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui widgets
SOURCES += AI_Player.cpp Arena.cpp Bomb.cpp CollisionBlock.cpp ExplosionBlock.cpp FragileBlock.cpp Game.cpp GameObject.cpp GroundBlock.cpp Item.cpp Menu.cpp Player.cpp SolidBlock.cpp main.cpp
HEADERS += AI_Player.h Arena.h Bomb.h CollisionBlock.h ExplosionBlock.h FragileBlock.h Game.h GameObject.h GroundBlock.h Item.h Menu.h Player.h SolidBlock.h
FORMS +=
RESOURCES += res.qrc
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU_MinGW-Windows-Windows
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
