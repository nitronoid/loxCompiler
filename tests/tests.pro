TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += $$files(../compiler/src/*.cpp)
SOURCES += test.cpp

INCLUDEPATH = ../compiler/include

HEADERS += $$files(../compiler/include/*.h)

LIBS += -lgtest -lgmock -pthread

QMAKE_CXXFLAGS += -std=c++1z
