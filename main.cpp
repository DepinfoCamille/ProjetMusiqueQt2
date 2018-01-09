#include "mainwindow.h"
#include "partition.h"
#include "audiooutputstreamer.h"

#include <windows.h>
#include <QApplication>
#include <QLabel>

#include <QAudioBuffer>
#include <QTextStream>
#include <QThread>

int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::vector<int> frequences ;
    frequences.push_back(800) ;
    frequences.push_back(700) ;
    frequences.push_back(600) ;

    std::vector<int> longueurs ;
    longueurs.push_back(8000) ; // en ms
    longueurs.push_back(1800) ;
    longueurs.push_back(4000) ;

    QThread thread ;

    for(int i = 0 ; i < 3 ; i++){

       AudioOutputStreamer* pAudioOutputStreamer = new AudioOutputStreamer(longueurs[i],frequences[i]);
  //      pAudioOutputStreamer->setFrequency(frequences[i]);
  //      pAudioOutputStreamer->setLenght(longueurs[i]);
        pAudioOutputStreamer->start();
        thread.msleep (longueurs[i]/*/100*/) ;
        std::cout << "On joue la fréquence" << frequences[i] << std::endl ;
        std::cout << "On attend " << longueurs[i]/*/100*/ << "ms/µs" << std::endl ;

    }

 //   pAudioOutputStreamer->setFrequency(500);
  //  pAudioOutputStreamer->setLenght(111100);
  //  AudioOutputStreamer* pAudioOutputStreamer = new AudioOutputStreamer();
   // pAudioOutputStreamer->start();
 /*   pAudioOutputStreamer->setFrequency(800);
    pAudioOutputStreamer->setLenght(91100);
    pAudioOutputStreamer->start();*/

 /*   QCoreApplication app(argc, argv);
    Console console;
    console.run();
    QObject::connect(&console, SIGNAL(quit()), &app, SLOT(quit()));
    app.exec();*/

    return a.exec();
}

