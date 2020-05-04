include (../config.pri)

TEMPLATE = app
DESTDIR = ../bin
TARGET = Joonistamine

SOURCES += \
    Point2.cpp \
    drawingwidget.cpp \
    main.cpp \
    mainwindow.cpp
HEADERS += \
    DynamicLine.h \
    Point2.h \
    drawingwidget.h \
    mainwindow.h
