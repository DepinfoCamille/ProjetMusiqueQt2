#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QString>
#include <QPixmap>
#include <QLabel>
#include <vector>

#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include <time.h>
#include <conio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    this->p = new Partition() ;
    this->dialogue = new BoitedeDialogue() ;

    ui->setupUi(this);
    QWidget *pic = new QWidget(this);
    pic->setStyleSheet("background-image: url(C:/Users/User/Desktop/2A/C++/5lignes.png)");
    pic->setGeometry(QRect(30,30,300,370));
    ui->CLE->addItem("Clé de Sol");
    ui->CLE->addItem("Clé de Fa");

    ui->textEdit->hide() ;


    QObject::connect(ui->CLE, SIGNAL(currentIndexChanged(int)), this,
                     SLOT(affichecle()));
    QObject::connect(ui->boutonEcrirePartition, SIGNAL(clicked()), this,
                     SLOT(afficherTexte()));
    QObject::connect(ui->textEdit, SIGNAL(textChanged()), this,
                     SLOT(ecrirePartition()));
}

void MainWindow::affichecle()
{
    int cle = ui->CLE->currentIndex();
    if (cle == 0 ){
        //Il manque une commande pour effacer l'existant
        QLabel *picture = new QLabel( this );
        picture -> setGeometry(25,35,55,65);
        picture ->setPixmap( QPixmap( "C:/Users/User/Desktop/2A/C++/cledesol.png" ) );
        picture ->setScaledContents(true);
        picture -> show();
    }
    if (cle == 1){
        //Il manque une commande pour effacer la clé existante
        QLabel *picture = new QLabel( this );
        picture -> setGeometry(40,40,40,44);
        picture ->setPixmap( QPixmap( "C:/Users/User/Desktop/2A/C++/cledefa.png" ) );
        picture ->setScaledContents(true);
        picture -> show();

    }
/*
    void MainWindow::affichedo(position, ligne, octave){
        if (octave == 3){
        }
    }
    */

}

void MainWindow::ecrirePartition() {

 /*   std::cout << "Ecrivez votre partition ici : " << std::endl ;
    QTextStream stream(stdin) ;

    clock_t start = clock(), diff;
    char caractere = stream.padChar().toLatin1() ;
    std::cout << caractere << std::endl ;*/

    QString notes = ui->textEdit->toPlainText() ;
    char note = notes[notes.size()-1].toLatin1() ;
    clock_t temps = clock() ;

    if(note!='\n'){
        this->p->ajoutNote(note) ;
        std::cout <<"note : " << note << std::endl ;
        std::cout <<"temps : " << temps << std::endl ;

        this->p->ajoutTemps(temps) ;
    }
    else{
        this->p->ajoutTemps(temps) ;
    }
    //ui->textEdit->clear() ;
}

void MainWindow::afficherTexte(){
    ui->textEdit->show() ;
}

MainWindow::~MainWindow()
{
    delete ui;
}
