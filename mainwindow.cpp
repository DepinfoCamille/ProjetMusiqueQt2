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

#include <windows.h>
#include <time.h>
#include <conio.h>
#include <string.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    // Initialisation des données
    this->p = new Partition() ;

    // Préparation de l'affichage
    ui->setupUi(this);

    ui->dialogue->setParent(ui->centralWidget);
    ui-> dialogue -> setVisible(FALSE);

    // Affichage du choix de la clé et de la taille de la mesure

    ui->CLE->addItem("Cle de Sol");
    ui->CLE->addItem("Cle de Fa");
    QObject::connect(ui->CLE, SIGNAL(currentIndexChanged(int)), this,
                     SLOT(affichecle()));
    ui->CLE->setCurrentIndex(0);

    // Emplacement des clés
    char *path=nullptr ;
    size_t size = 0 ;
    path=GetCurrentDir(path,size);
    std::cout <<"rep courant " <<path << std::endl ;

    char* repCleSol = (char*) malloc(sizeof(char)*(strlen(path)+31)) ;
    strcpy(repCleSol,path) ;
    strcat(repCleSol,"\\..\\ProjetMusiqueQt2\\cleSol.png") ;

    std::cout << "rep path après = " << path << std::endl ;
    std::cout <<"rep sol " <<repCleSol << std::endl ;


    ui->cledeSol_2 -> setGeometry(27,38,55,65);
    ui->cledeSol_2->setPixmap( QPixmap( repCleSol) );
    ui->cledeSol_2->setScaledContents(true);
    ui->cledeSol_2-> show();

    ui -> MESURE -> addItem("Cliquez ici pour choisir une mesure");
    ui ->MESURE ->addItem(" 2 / 4 ");
    ui -> MESURE ->addItem(" 3 / 4 ");
    ui -> MESURE ->addItem(" 4 / 4 ");

    // Initialisation du Widget permettant de dessiner les notes
        this -> an = new Affichernotes();
         this->an->setParent(ui->frame);

    // Connexion des différents objets entre eux

    // Première étape : on initialise la partition et l'affichage
    QObject::connect(ui->boutonEcrirePartition, SIGNAL(clicked()), this,
                     SLOT(initialisation()));

    // Deuxième étape : on choisit le type de mesure voulue
    QObject::connect(this, SIGNAL(initFaite()), this,
                     SLOT(affichemesure()));

    // Troisième étape : on choisit le tempo
    QObject::connect(ui->MESURE, SIGNAL(currentIndexChanged(int)), this,
                     SLOT(afficherTempo()));
    QObject::connect(ui->boutonTempo, SIGNAL(clicked()), this,
                     SLOT(choisirTempo()));

    // Quatrième étape : l'utilisateur joue son morceau au clavier
    QObject::connect(this, SIGNAL(tempoDefini()), this,
                     SLOT(afficherCreationPartition()));
    QObject::connect(ui->textEdit, SIGNAL(textChanged()), this,
                     SLOT(ecrirePartition()));

    // Cinquième étape : l'utilisateur peut écouter son morceau
    //                   et/ou voir sa partition
    QObject::connect(this, SIGNAL(partitionEcrite()), this,
                     SLOT(afficherEcouterPartition()));
    QObject::connect(ui->boutonEcouter, SIGNAL(clicked()), this,
                     SLOT(ecouterPartition()));
    QObject::connect(ui->boutonvoirpartition, SIGNAL(clicked()), this,
                     SLOT(voirPartition()));

    //Sixième étape: modification de la partition déjà écrite
    QObject::connect(ui->frame, SIGNAL(clicked()), this, SLOT(positioncurseur()));

}

void MainWindow::initialisation(){
    this->p->initPartition();
    ui->MESURE->setCurrentIndex(0);
    ui->textEdit->setOverwriteMode(true); ;
    emit initFaite() ;

}

void MainWindow::affichemesure(){

    ui->dialogue->setVisible(TRUE);
    ui->dialogue->setCurrentIndex(0);

    int mesure = ui->MESURE->currentIndex();

    if (mesure == 1){
        ui->mesure1_2 -> setText("2\n4");
        this->an->mesure = 2;
    }
    if (mesure == 2){
        ui->mesure1_2 -> setText("3\n4");
        this->an->mesure = 3;
    }
    if (mesure == 3){
        ui->mesure1_2 -> setText("4\n4");
        this->an->mesure = 4;
    }
 //   ui->mesure1_2->setParent(ui->centralWidget);
   // ui->mesure1_2->show();
}

void MainWindow::afficherTempo(){
    ui->dialogue->setCurrentIndex(1);
}

void MainWindow::afficherCreationPartition(){
    ui->dialogue->setCurrentIndex(2) ;
    ui->boxEcrirePartition->show() ;
    ui->textEdit->setReadOnly(false);
    ui->textEdit->hide() ;
}

void MainWindow::afficherEcouterPartition(){
    this->p->calculDuree() ;
    this->p->creeRythme() ;
    ui->dialogue->setCurrentIndex(3) ;
    ui->boxPartitionEcrite->show() ;
   // ui->textEdit->clear() ;
    ui->textEdit->show() ;

}

/** Cette fonction est lancée lorsque l'utilisateur appuie sur "Tempo"
 * Elle remplit une liste contenant le moment où l'utilisateur appuie sur le bouton
 */
void MainWindow::choisirTempo(){
    clock_t start = clock() ;
/*    int i = 0 ;
    while(this->p->listePulsations[i]!=0){
        i++;
    }
    if(i<4){
        this->p->listePulsations[i] = 1000*start/(float)CLOCKS_PER_SEC ;
    }*/
    int i = this->p->setTempo(1000*start/(float)CLOCKS_PER_SEC);

    if(i==3){

        this->p->tempo = (this->p->listePulsations[3]-this->p->listePulsations[0])/3 ;
        emit tempoDefini() ;
        ui->page->hide() ;
    }
}
/** @brief affiche une clé de sol ou une clé de fa, au choix */
void MainWindow::affichecle()
{

    // Emplacement des clés
    char *path=nullptr ;
    size_t size = 0 ;
    path=GetCurrentDir(path,size);

    char* repCleSol = (char*) malloc(sizeof(char)*(strlen(path)+50)) ;
    char* repCleFa = (char*) malloc(sizeof(char)*(strlen(path)+50)) ;

    strcpy(repCleSol,path) ;
    strcat(repCleSol,"\\..\\ProjetMusiqueQt2\\cleSol.png") ;


    strcpy(repCleFa,path) ;
    strcat(repCleFa,"\\..\\ProjetMusiqueQt2\\cleFa.png") ;

    int cle = ui->CLE->currentIndex();

    // Clé de sol
    if (cle == 0){
        ui->cledeSol_2 -> setGeometry(27,38,55,65);
        ui->cledeSol_2->setPixmap( QPixmap(repCleSol) );
        ui->cledeSol_2->setScaledContents(true);
        ui->cledeSol_2-> show();
    }

    // CLé de fa
    if (cle == 1){

       // QLabel *picture = new QLabel( this );
        ui->cledeSol_2 -> setGeometry(27,43,40,44);
        ui->cledeSol_2 ->setPixmap( QPixmap(repCleFa) );
        ui->cledeSol_2 ->setScaledContents(true);
        ui->cledeSol_2 -> show();
    }
}

/** @brief Cette fonction est appelée quand l'utilisateur tape sur une touche de son clavier
 * Elle ajoute la note correspondant à la touche tapée à la partition
 * Lorsque l'utilisateur tape sur entrée, la partition est considérée comme finie
 */
void MainWindow::ecrirePartition() {

    // On lit la note tapée au clavier
    QString notes = ui->textEdit->toPlainText() ;
    char note = notes[notes.size()-1].toLatin1() ;
    clock_t temps = clock() ;

    // Si l'utilisateur n'a pas tapé sur entrée,
    // on enregistre la note
    if((int)note!=10){

        int noteLongue = this->p->ajoutTemps(temps) ;

        if(!noteLongue){
            this->p->ajoutNote(note) ;
        }

    }
    else{
        this->p->ajoutTemps(temps) ;
        emit partitionEcrite();
    }
  //  ui->textEdit->setOverwriteMode(false);
}

void MainWindow::ecouterPartition(){

    this->p->jouer() ;
}

void MainWindow::voirPartition(){

    // Emplacement des clés
    char *path=nullptr ;
    size_t size = 0 ;
    path=GetCurrentDir(path,size);

    char* repCleSol = (char*) malloc(sizeof(char)*(strlen(path)+50)) ;
    char* repCleFa = (char*) malloc(sizeof(char)*(strlen(path)+50)) ;

    strcpy(repCleSol,path) ;
    strcat(repCleSol,"\\..\\ProjetMusiqueQt2\\cleSol.png") ;


    strcpy(repCleFa,path) ;
    strcat(repCleFa,"\\..\\ProjetMusiqueQt2\\cleFa.png") ;

    this->an->update();
    this->an->listeNotes =this->p->listeNotes ;
    this->an->listeTemps = this->p->listeRythme;
    this->an->listeOctaves=this->p->listeOctave;
    int mesure = ui->MESURE->currentIndex();
    int indexCle = ui->CLE->currentIndex() ;

    if ( this->an->listeNotes.size() >15 ) {

        for (int i=1; i <=(int)this->an->listeNotes.size()/15; i++){
            QLabel *cle= new QLabel(this);
            QLabel *copiemesure = new QLabel(this);


            if(indexCle==0){
                cle ->setPixmap(QPixmap( repCleSol ));
                cle ->setScaledContents(true);
                cle -> show();
                cle->setGeometry(27,43+96*i,55,65);
            }
            if(indexCle==1){
                cle ->setPixmap(QPixmap( repCleFa ));
                cle ->setScaledContents(true);
                cle -> show();
                cle->setGeometry(27,43+96*i,55,65);
            }

            if (mesure == 1){
                copiemesure -> setText("2\n4");
            }
            if (mesure == 2){
                copiemesure -> setText("3\n4");
            }
            if (mesure == 3){
                copiemesure -> setText("4\n4");
            }
                copiemesure->setGeometry(90,40+98*i,47,51);
                copiemesure->show();
                copiemesure ->setFont(QFont("Source Code Pro ",14,QFont::Bold));

        }
    }
}

void MainWindow::positioncurseur(){
  //  pos = QCursor.pos();
    std::cout<<"qjdhf";
}



MainWindow::~MainWindow()
{
    delete ui;
}
