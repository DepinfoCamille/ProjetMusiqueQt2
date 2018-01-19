#include "mainwindow.h"
#include "partition.h"
#include "audiooutputstreamer.h"

#include <windows.h>
#include <QApplication>
#include <QLabel>

#include <QAudioBuffer>
#include <QTextStream>
#include <QThread>
#include <QMediaPlayer>

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif


int main(int argc, char *argv[]){


    QApplication a(argc, argv);
    char* cd = nullptr ;
    /*cd = malloc(sizeof(char*)) ;
    GetCurrentDir(cd,sizeof(char*));
    std::cout << cd << std::endl ;*/
    MainWindow w;

    w.show();

    return a.exec();
}

