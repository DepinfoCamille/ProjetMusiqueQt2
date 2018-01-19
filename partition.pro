#-------------------------------------------------
#
# Project created by QtCreator 2017-12-13T10:15:02
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = partition
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    partition.cpp \
    audiooutputstreamer.cpp \
    affichernotes.cpp

HEADERS += \
        mainwindow.h \
    partition.h \
    audiooutputstreamer.h \
    affichernotes.h

FORMS += \
        mainwindow.ui

# Ajout de la librairie OpenAL

#INCLUDEPATH += D:\ProjetMusique\testMidiQt\QMidi-master\src # chemin des .h
#LIBS += -LD:\ProjetMusique\testMidiQt\QMidi-master\src #chemin de la librairie


DISTFILES += \
    partition.pro.user


#INCLUDEPATH += "C:\Program Files (x86)\OpenAL 1.1 SDK\include" # chemin des .h
#LIBS += -L"$$_PRO_FILE_PWD_C:\Program Files (x86)\OpenAL 1.1 SDK\libs\Win32" -lOpenAL32


INCLUDEPATH += "D:\ProjetMusique\portaudio\include"
LIBS += -L"D:\ProjetMusique\portaudio\src"

INCLUDEPATH += "D:\ProjetMusique\openal-soft\include"

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../portaudio/build/release/ -lportaudio_x86
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../portaudio/build/debug/ -lportaudio_x86
else:unix: LIBS += -L$$PWD/../../portaudio/build/ -lportaudio_x86

INCLUDEPATH += $$PWD/../../portaudio/build/Debug
DEPENDPATH += $$PWD/../../portaudio/build/Debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../openal-soft/build/release/ -lOpenAL32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../openal-soft/build/debug/ -lOpenAL32
else:unix: LIBS += -L$$PWD/../../openal-soft/build/ -lOpenAL32

INCLUDEPATH += $$PWD/../../openal-soft/build/Debug
DEPENDPATH += $$PWD/../../openal-soft/build/Debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../SFML/build/lib/release/ -lsfml-audio-d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../SFML/build/lib/debug/ -lsfml-audio-d
else:unix: LIBS += -L$$PWD/../../SFML/build/lib/ -lsfml-audio-d

INCLUDEPATH += $$PWD/../../SFML/build/lib/Debug
DEPENDPATH += $$PWD/../../SFML/build/lib/Debug

INCLUDEPATH += "D:\ProjetMusique\SFML\include"
LIBS += -L"D:\ProjetMusique\SFML\src"
