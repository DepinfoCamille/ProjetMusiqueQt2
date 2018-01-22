#include "mainwindow.h"
#include "partition.h"
#include "audiooutputstreamer.h"

#include <windows.h>
#include <QApplication>
#include <QMediaPlaylist>
#include <QMediaPlayer>


int main(int argc, char *argv[]){


    QApplication a(argc, argv);

    MainWindow w;

    w.show();

    QSound sonIntro("D:\\ProjetMusique\\ProjetMusiqueQt\\ProjetMusiqueQt2\\DO3.wav") ;
    sonIntro.play() ;

    return a.exec();
}

