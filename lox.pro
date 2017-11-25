TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += $$files(./src/*.cpp)

INCLUDEPATH = include

HEADERS += $$files(./include/*.h)

QMAKE_CXXFLAGS += -std=c++1z
