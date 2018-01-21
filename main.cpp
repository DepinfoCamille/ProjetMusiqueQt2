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

    QMediaPlaylist* playlist = new QMediaPlaylist() ;

    std::cout << "new playlist" << std::endl ;
    playlist->addMedia(QUrl("D:\ProjetMusique\ProjetMusiqueQt\ProjetQt2\DO3.mp3"));

    std::cout << "addMedia" << std::endl ;

    QMediaPlayer* player = new QMediaPlayer() ;

    player->setPlaylist(playlist) ;
    player->play() ;


    return a.exec();
}

