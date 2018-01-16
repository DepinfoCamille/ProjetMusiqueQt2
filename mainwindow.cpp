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


#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
 /*   char buffer[200];
    GetCurrentDir(buffer, sizeof(buffer) );*/

    // Initialisation des données
    this->p = new Partition() ;
    QString titre ;
    //titre.fromLatin1(buffer + "D:/ProjetMusique/ProjetMusiqueQt/build-partition-Desktop_Qt_5_10_0_MinGW_32bit-Debug/debug/morceau.wav") ;
    //this->lecture = new QSound(titre) ;

    // Préparation de l'affichage
    ui->setupUi(this);
    ui->page->hide() ;
    ui->boxEcrirePartition->hide() ;
    ui->boxPartitionEcrite->hide() ;

    // Affichage du choix de la clé et de la taille de la mesure
    ui->setupUi(this);
    ui->CLE->addItem("Cle de Sol");
    ui->CLE->addItem("Cle de Fa");
    QObject::connect(ui->CLE, SIGNAL(currentIndexChanged(int)), this,
                     SLOT(affichecle()));

    ui->cledeSol_2 -> setGeometry(27,38,55,65);
    ui->cledeSol_2->setPixmap( QPixmap( "C:/Users/User/Desktop/2A/C++/cledeSol.png" ) );
    ui->cledeSol_2->setScaledContents(true);
    ui->cledeSol_2-> show();

    ui -> MESURE -> addItem("Cliquez ici pour choisir une mesure");
    ui ->MESURE ->addItem(" 2 / 4 ");
    ui -> MESURE ->addItem(" 3 / 4 ");
    ui -> MESURE ->addItem(" 4 / 4 ");

    // Initialisation du Widget permettant de dessiner les notes
        this -> an = new Affichernotes();
         this->an->setParent(ui->frame);


    QObject::connect(ui->MESURE, SIGNAL(currentIndexChanged(int)), this,
                     SLOT(affichemesure()));

   // QObject::connect(ui->MESURE, SIGNAL(currentIndexChanged(int)), this,
   //                  SLOT(mesurepartition()));

    // Première étape : l'utilisateur détermine le tempo
    QObject::connect(ui->boutonEcrirePartition, SIGNAL(clicked()), this,
                     SLOT(afficherTempo()));
    QObject::connect(ui->boutonTempo, SIGNAL(clicked()), this,
                     SLOT(choisirTempo()));
    // Deuxième étape : l'utilisateur joue son morceau au clavier
    QObject::connect(this, SIGNAL(tempoDefini()), this,
                     SLOT(afficherCreationPartition()));
    QObject::connect(ui->textEdit, SIGNAL(textChanged()), this,
                     SLOT(ecrirePartition()));
    // Troisième étape : on affiche la partition, et s'il le veut,
    // l'utilisateur peut écouter son morceau
    QObject::connect(this, SIGNAL(partitionEcrite()), this,
                     SLOT(afficherEcouterPartition()));
    QObject::connect(ui->boutonEcouter, SIGNAL(clicked()), this,
                     SLOT(ecouterPartition()));
    QObject::connect(ui->boutonvoirpartition, SIGNAL(clicked()), this,
                     SLOT(voirPartition()));
}


void MainWindow::afficherTempo(){
    ui->dialogue->setCurrentIndex(0);
}

void MainWindow::afficherCreationPartition(){
    ui->dialogue->setCurrentIndex(1) ;
    ui->boxEcrirePartition->show() ;
}

void MainWindow::afficherEcouterPartition(){
    std::cout << " \n On est dans calculDuree \n" << std::endl ;
    this->p->calculDuree() ;
    std::cout << " \n On est dans creerRythme \n" << std::endl ;
    this->p->creeRythme() ;
    ui->dialogue->setCurrentIndex(2) ;
    ui->boxPartitionEcrite->show() ;
}

/** Cette fonction est lancée lorsque l'utilisateur appuie sur "Tempo"
 * Elle remplit une liste contenant le moment où l'utilisateur appuie sur le bouton
 */
void MainWindow::choisirTempo(){
    clock_t start = clock() ;
    int i = 0 ;
    while(this->p->listePulsations[i]!=0){
        i++;
    }
    if(i<4){
        this->p->listePulsations[i] = 1000*start/(float)CLOCKS_PER_SEC ;
    }
    if(i==3){

        for(int j = 0 ; j < 4 ; j++){
            std::cout << "tempo numéro " << j << " : " << this->p->listePulsations[j] << std::endl ;
        }

        this->p->tempo = (this->p->listePulsations[3]-this->p->listePulsations[0])/3 ;
        std::cout << "tempo " << this->p->tempo << std::endl ;
        emit tempoDefini() ;
        ui->page->hide() ;
    }
}

void MainWindow::affichecle()
{
    int cle = ui->CLE->currentIndex();
    if (cle == 0 ){

        ui->cledeSol_2 -> setGeometry(27,38,55,65);
        ui->cledeSol_2->setPixmap( QPixmap( "C:/Users/User/Desktop/2A/C++/cledesol.png" ) );
        ui->cledeSol_2->setScaledContents(true);
        ui->cledeSol_2-> show();

    }
    if (cle == 1){

       // QLabel *picture = new QLabel( this );
        ui->cledeSol_2 -> setGeometry(27,43,40,44);
        ui->cledeSol_2 ->setPixmap( QPixmap( "C:/Users/User/Desktop/2A/C++/cledefa.png" ) );
        ui->cledeSol_2 ->setScaledContents(true);
        ui->cledeSol_2 -> show();
    }
}

/** Cette fonction est appelée quand l'utilisateur tape sur une touche de son clavier
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
            std::cout <<"note : " << note << std::endl ;
     //       std::cout <<"temps : " << temps << std::endl ;
        }

    }
    else{
        this->p->ajoutTemps(temps) ;
        emit partitionEcrite();
    }
}

void MainWindow::ecouterPartition(){
    int i = 0 ;
    std::cout << " \n On est à l'affichage des fréquences" << std::endl ;

    for(auto it = this->p->dicco_frequence.begin() ; it!=this->p->dicco_frequence.end() ; it++){
        std::cout << this->p->dicco_frequence[i++] << " " ;
    }
    std::cout << " \n On a passé l'affichage des fréquences" << std::endl ;
    this->p->jouer() ;
}

void MainWindow::affichemesure()
{
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

}
void MainWindow::voirPartition(){

    this->an->update();
    this->an->listeNotes =this->p->listeNotes ;
    this->an->listeTemps = this->p->listeRythme;
    this->an->listeOctaves=this->p->listeOctave;

}



MainWindow::~MainWindow()
{
    delete ui;
}
