#include "mainwindow.h"
#include "partition.h"
#include "audiooutputstreamer.h"

#include <windows.h>
#include <QApplication>


int main(int argc, char *argv[]){


    QApplication a(argc, argv);

    MainWindow w;

    w.show();

    return a.exec();
}

