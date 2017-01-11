#-------------------------------------------------
#
# Project created by QtCreator 2016-08-26T14:04:54
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = painter_mouse
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    playwidget.cpp \
    logicasudoku.cpp \
    camera.cpp

HEADERS  += mainwindow.h \
    playwidget.h \
    logicasudoku.h \
    camera.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

