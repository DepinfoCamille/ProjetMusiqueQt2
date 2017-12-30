#include "mainwindow.h"
#include "partition.h"
#include "son.h"
#include "consolereader.h"

#include <windows.h>
#include <QApplication>
#include <QLabel>

#include <QAudioBuffer>
#include <QTextStream>


int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


 /*   QCoreApplication app(argc, argv);
    Console console;
    console.run();
    QObject::connect(&console, SIGNAL(quit()), &app, SLOT(quit()));
    app.exec();*/

    return a.exec();
}

