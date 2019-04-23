#-------------------------------------------------
#
# Project created by QtCreator 2018-01-06T13:22:43
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = X325
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwnd.cpp \
    commonLogger.cpp \
    Views/viewInterface.cpp \
    Views/viewAddFormats.cpp \
    Menu/menuButton.cpp \
    Menu/menuToolBar.cpp \
    Views/viewsManager.cpp \
    Views/viewMaterials.cpp \
    dbManager.cpp \
    undoStack.cpp \
    Views/viewFurnitures.cpp

HEADERS  += mainwnd.h \
    commonLogger.h \
    Views/viewInterface.h \
    Views/viewAddFormats.h \
    version.h \
    Menu/menuButton.h \
    Menu/menuToolBar.h \
    Views/viewsManager.h \
    Views/viewMaterials.h \
    dbManager.h \
    undoStack.h \
    Views/viewFurnitures.h

FORMS    += mainwnd.ui \
    Views/viewaddformatsUI.ui \
    Views/viewMaterials.ui \
    Views/viewFurnitures.ui

RESOURCES += \
    resources.qrc
