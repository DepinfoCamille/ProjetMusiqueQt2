#include "mainwindow.h"
#include "partition.h"
#include "son.h"

#include <windows.h>
#include <QApplication>
#include <QLabel>

#include <QAudioBuffer>
#include <QTextStream>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

 /*   Partition *p = new Partition() ; // faire une fonction create partition
    Son* son = new Son(p) ;

    QTextStream stream(stdin) ;

    int lecture = 0 ;
    // lecture clavier
    while(lecture==0){
        lecture = son->partition->lectureClavier() ;
    }
/*    son->lecturePartition(son->partition) ;*/

    return a.exec();
}

