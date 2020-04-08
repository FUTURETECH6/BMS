#-------------------------------------------------
#
# Project created by QtCreator 2020-04-04T09:22:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BMS
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
INCLUDEPATH += ./include/
INCLUDEPATH += /usr/local/Cellar/mysql/8.0.19/include/mysql/
LIBS += -L/usr/local/Cellar/mysql/8.0.19/lib/ -lmysqlclient

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        ./Src/Database.cpp   \
        ./Src/adminpad.cpp   \
        ./Src/borret.cpp     \
        ./Src/insbookpad.cpp \
        ./Src/inscardpad.cpp \
        ./Src/login.cpp      \
        ./Src/main.cpp       \
        ./Src/mainwindow.cpp \
        ./Src/querypad.cpp   \
        ./Src/insadminpad.cpp

HEADERS +=                     \
        ./include/Database.h   \
        ./include/adminpad.h   \
        ./include/borret.h     \
        ./include/insbookpad.h \
        ./include/inscardpad.h \
        ./include/login.h      \
        ./include/mainwindow.h \
        ./include/querypad.h   \
        ./include//insadminpad.h

FORMS += \
    ./UI/adminpad.ui   \
    ./UI/borret.ui     \
    ./UI/insbookpad.ui \
    ./UI/inscardpad.ui \
    ./UI/login.ui      \
    ./UI/mainwindow.ui \
    ./UI/querypad.ui   \
    ./UI/insadminpad.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
