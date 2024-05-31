QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtMineSweep
TEMPLATE = app


SOURCES += main.cpp\
        main_game_window.cpp \
    game_model.cpp

HEADERS  += main_game_window.h \
    game_model.h

FORMS    += maingamewindow.ui

RESOURCES += \
    resource.qrc
