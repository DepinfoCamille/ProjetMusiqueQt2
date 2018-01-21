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

    QSound test("D:\\ProjetMusique\\ProjetMusiqueQt\\ProjetMusiqueQt2\\DO3.wav") ;
    QSound test2("D:\\ProjetMusique\\ProjetMusiqueQt\\ProjetMusiqueQt2\\DO4.wav") ;
    QSound silence("D:\\ProjetMusique\\ProjetMusiqueQt\\ProjetMusiqueQt2\\SILENCE.wav") ;


    clock_t start = clock();
    clock_t temps = clock() ;
    std::cout << " debut son" << std::endl ;
    test.play() ;

    std::cout << " fin son" << std::endl ;




/*    QMediaPlaylist* playlist = new QMediaPlaylist() ;

    std::cout << "new playlist" << std::endl ;
    playlist->addMedia(QUrl("D:/ProjetMusique/ProjetMusiqueQt/ProjetQt2/FormatFactoryDO3.mp3"));

    std::cout << "addMedia" << std::endl ;

    QMediaPlayer* player = new QMediaPlayer() ;

    player->setPlaylist(playlist) ;
    player->play() ;

    if (player->error() == QMediaPlayer::FormatError)
    {
        std::cout << "format non supporté " << std::endl ;
    }*/


    return a.exec();
}

