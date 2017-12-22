#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QString>
#include <QPixmap>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *pic = new QWidget(this);
    pic->setStyleSheet("background-image: url(C:/Users/User/Desktop/2A/C++/5lignes.png)");
    pic->setGeometry(QRect(30,30,300,370));
    ui->CLE->addItem("Cle de Sol");
    ui->CLE->addItem("Cle de Fa");
    QObject::connect(ui->CLE, SIGNAL(currentIndexChanged(int)), this,
                     SLOT(affichecle()));


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

MainWindow::~MainWindow()
{
    delete ui;
}
