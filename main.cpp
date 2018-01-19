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

    char *path=NULL;
    size_t size;
    path=GetCurrentDir(path,size);
    std::cout<<"\n current Path "<<path << " size " <<size;
    std::cout << std::endl ;

 //   char str[] ="/path/to/file";
  /*  char * pch;
    char * temp;
    pch = strtok (path,(char*)43);
    while ( (temp = strtok (NULL, (char*)43) ) != NULL)
    {
      pch = temp;
    }

    std::cout << "The file is: " << pch << std::endl;*/

    MainWindow w;

    w.show();

    return a.exec();
}

