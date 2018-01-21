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
#include "ecouterpartition.h"
#include <QSound>


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

    char* repCleSol = (char*) malloc(sizeof(char)*(strlen(path)+31)) ;
    strcpy(repCleSol,path) ;
    strcat(repCleSol,"\\..\\ProjetMusiqueQt2\\cleSol.png") ;

    QLabel* cle = new QLabel(this) ;
    cle -> setGeometry(27,50,55,65);
    cle ->setPixmap( QPixmap( repCleSol) );
    cle ->setScaledContents(true);
    cle -> show();
    this->clesDebutLignes.push_back(cle);

    ui -> MESURE -> addItem("Cliquez ici pour choisir une mesure");
    ui ->MESURE ->addItem(" 2 / 4 ");
    ui -> MESURE ->addItem(" 3 / 4 ");
    ui -> MESURE ->addItem(" 4 / 4 ");

    // Initialisation du Widget permettant de dessiner les notes
        this -> an = new Affichernotes();
         this->an->setParent(ui->frame);
        this->an->estCledeSol = true ;

    // Connexion des différents objets entre eux

    // Première étape : on initialise la partition et l'affichage
    QObject::connect(ui->boutonEcrirePartition, SIGNAL(clicked()), this,
                     SLOT(initialisation()));

    // Deuxième étape : on choisit le type de mesure voulue
    QObject::connect(this, SIGNAL(initFaite()), this,
                     SLOT(afficherboxmesure()));

    // Troisième étape : on choisit le tempo
    QObject::connect(ui->MESURE, SIGNAL(currentIndexChanged(int)), this,
                     SLOT(choixmesure()));
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
    QObject::connect(ui->boutonModifier, SIGNAL(clicked()), this, SLOT(changerPartition()));

}

void MainWindow::initialisation(){

    this->p->initPartition();
    this->partitionAffichee = false  ;
    ui->MESURE->setCurrentIndex(0);
    ui->textEdit->setOverwriteMode(true);
    this->an->hide() ;
    this->an->estCledeSol = true ;

    if(this->clesDebutLignes.size()!=1){
        for(auto cle = this->clesDebutLignes.begin()+1 ; cle != this->clesDebutLignes.end() ; cle++){
            (*cle)->clear() ;
        }
        this->clesDebutLignes.clear() ;
    }

    // Affichage de la clé de sol
 /*       char *path=nullptr ;
        size_t size = 0 ;
        path=GetCurrentDir(path,size);
        QLabel *cle= new QLabel(this);
        char* repCleSol = (char*) malloc(sizeof(char)*(strlen(path)+31)) ;
        strcpy(repCleSol,path) ;
        strcat(repCleSol,"\\..\\ProjetMusiqueQt2\\cleSol.png") ;

        cle-> setGeometry(27,38,55,65);
        cle->setPixmap( QPixmap( repCleSol) );
        cle->setScaledContents(true);
        cle-> show();
        this->clesDebutLignes.push_back(cle);*/
    if(!this->mesureDebutLignes.empty()){
        for(auto mesure = this->mesureDebutLignes.begin() ; mesure != this->mesureDebutLignes.end() ; mesure++){
            (*mesure)->clear() ;
        }
        this->mesureDebutLignes.clear() ;
    }

    if(!this->p->listebuttons.empty()){
        for(auto bouton = this->p->listebuttons.begin() ; bouton != this->p->listebuttons.end() ; bouton++){
            delete (*bouton) ;
        }
        this->p->listebuttons.clear() ;
    }

    emit initFaite() ;

}
void MainWindow::afficherboxmesure(){
    ui->dialogue->setVisible(TRUE);
    ui->dialogue->setCurrentIndex(0);

}
void MainWindow::choixmesure(){

    int mesure = ui->MESURE->currentIndex();

    if (mesure == 1){
        ui->mesure1_2 -> setText("2\n4");
        this->an->mesure = 2;
    }
    else if (mesure == 2){
        ui->mesure1_2 -> setText("3\n4");
        this->an->mesure = 3;
    }
    else if (mesure == 3){
        ui->mesure1_2 -> setText("4\n4");
        this->an->mesure = 4;
    }
    ui->dialogue->setCurrentIndex(1);

}



void MainWindow::afficherCreationPartition(){
    ui->dialogue->setCurrentIndex(2) ;
    ui->boxEcrirePartition->show() ;
    ui->textEdit->setReadOnly(false);
    ui->textEdit->hide() ;

}

void MainWindow::afficherEcouterPartition(){
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

    int i = this->p->setTempo(1000*start/(float)CLOCKS_PER_SEC);

    if(i==3){

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
        int i = 0 ;
        for(auto cle = this->clesDebutLignes.begin() ; cle != this->clesDebutLignes.end() ; cle++){
            (*cle)->clear();
            (*cle)->setPixmap(QPixmap( repCleSol));
            (*cle) ->setScaledContents(true);
            (*cle) -> show();
            (*cle)->setGeometry(27,50+91*i++,55,65);
        }
    }

    // CLé de fa
    if (cle == 1){
        this->an->estCledeSol = false ;
        int i = 0 ;
        for(auto cle = this->clesDebutLignes.begin() ; cle != this->clesDebutLignes.end() ; cle++){
            (*cle)->clear();
            (*cle) ->setPixmap(QPixmap( repCleFa ));
            (*cle) ->setScaledContents(true);
            (*cle) -> show();
            (*cle)->setGeometry(27,50+91*i++,50,65);
         }
    }
    if(this->partitionAffichee){
        this->voirPartition();
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

        this->p->ajoutTemps(temps) ;
        this->p->ajoutNote(note) ;
    }
    else{
        this->p->ajoutTemps(temps) ;
        emit partitionEcrite();
    }
}

void MainWindow::ecouterPartition(){

    std::cout << "Désolée, je n'ai pas réussi... pourtant j'y ai passé du temps !" << std::endl ;
}

/** @brief Cette fonction est appelée quand l'utilisateur tape sur le bouton 'Voir partition'
 * Elle envoie toute les informations nécessaires de la classe partition à la classe Afficher note
 */

void MainWindow::voirPartition(){

    this->an->clearFocus();
    this->an->clearMask();
    this->an->show() ;

    this->an->update();
    this->an->listeNotes =this->p->listeNotes ;
    this->an->listeTemps = this->p->listeRythme;
    this->an->listeOctaves=this->p->listeOctave;
    int mesure = ui->MESURE->currentIndex();
    int indexCle = ui->CLE->currentIndex() ;

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

    // On est dans le cas où il y a plusieurs lignes
    if ( this->an->listeNotes.size() >15 ) {

        for (int i=1; i <=(int)this->an->listeNotes.size()/15; i++){
            QLabel *cle= new QLabel(this);
            QLabel *copiemesure = new QLabel(this);

        if(!this->partitionAffichee){

            if(indexCle==0){ // clé de sol
                cle ->setPixmap(QPixmap( repCleSol));

                cle ->setScaledContents(true);
                cle -> show();
                cle->setGeometry(27,50+91*i,55,65);
//                cle -> setGeometry(27,50,55,65);

            }
            else if(indexCle==1){ //clé de fa
                cle ->setPixmap(QPixmap( repCleFa ));
                cle ->setScaledContents(true);
                cle -> show();
                cle->setGeometry(27,50+91*i,50,65);
            }
            this->clesDebutLignes.push_back(cle);
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
                this->mesureDebutLignes.push_back(copiemesure);

        }
    }
    this->partitionAffichee=true;
}

/** @brief Cette fonction est appelée quand l'utilisateur tape sur le bouton Modifier Partition
 * Elle créé un bouton invisible sur chaque note pourpouvoir les modifier
 */

void MainWindow::changerPartition(){
    // création d'un bouton invisible a l'emplacement de chaque note
    for (unsigned int i = 0; i<this->an->listeNotes.size(); i++){
        QPushButton *buttoni= new QPushButton(this);
        int j;
        j= i/15;
        buttoni->setGeometry(127 +(i-15*j)*35,60 + j*90,15,50);
        buttoni->setFlat(true);
        buttoni->show();

        this->p->listebuttons.push_back(buttoni);
        QObject::connect(this->p->listebuttons[i], SIGNAL(clicked()), this,
                         SLOT(affichercaracteristiquesnote()));
    }


    ui->explication->setText("Veuillez cliquer sur la note que vous désirez changer");
    ui->explication->show();
}


/** @brief Cette fonction est appelée quand l'utilisateur tape sur une note après avoir appuyé sur le bouton Modifier Partition
 * Elle fait apparaitre deux combobox ou l'utilisateur peut sélectionner ses changements
 */
void MainWindow::affichercaracteristiquesnote(){
    //affiche un label avec deux combobox pour pouvoir changer la note à modifier

    emit modifPartitionfaite();
    int i=0;
    QObject *modif = QObject::sender();
    while (this->p->listebuttons[i] != modif && i<10){
       i =i+1;
    }
    int j= i/15;
    this->information  = new QLabel(this) ;
    QComboBox *note = new QComboBox(this->information);
    QComboBox *tempo = new QComboBox(this->information);
    this->information ->setScaledContents(true);
    this->information->setGeometry(150 +(i-15*j)*35,120 + j*90,130,120);
    this->information->setText("    Veuillez choisir \n    votre modification \n \n \n \n \n \n");
    this->information->setStyleSheet("background-color: rgb(240, 243, 244)");
    this->information->show();
    connect(this,SIGNAL(modifPartitionfaite()),this, SLOT(cacherDialoguemodif())) ;

    //on enregistre l'indice de la note à changer
    indicenoteachanger=i;

    //valeurs possibles du combobox agissant sur les notes
    note ->addItem("notes");
    note ->addItem("DO3");
    note ->addItem("DO#3");
    note ->addItem("RE3");
    note ->addItem("RE#3");
    note ->addItem("MI3");
    note ->addItem("FA3");
    note ->addItem("FA#3");
    note ->addItem("SOL3");
    note ->addItem("SOL#3");
    note ->addItem("LA3");
    note ->addItem("LA#3");
    note ->addItem("SI3");
    note ->addItem("DO4");
    note ->addItem("DO#4");
    note ->addItem("RE4");


    note->move(30,42);
    QObject::connect(note, SIGNAL(currentIndexChanged(int)), this,
                     SLOT(changernote(int)));

    //valeurs possibles du combobox agissant sur le tempo
    tempo->addItem("tempo");
    tempo->addItem("NOIRE");
    tempo->addItem("BLANCHE");
    tempo->addItem("RONDE");
    tempo->addItem("CROCHE");
    tempo->addItem("NOIRE_POINTEE");
    tempo->addItem("BLANCHE_POINTEE");
    tempo->move(30,62);
    QObject::connect(tempo, SIGNAL(currentIndexChanged(int)), this,
                     SLOT(changertempo(int)));

}

/** @brief
 * Cette fonction met à jour les parametres de la partition de la classe partition
 * Elle appelle la fonction voirPartition pour que l'affichage se mette à jour
 */
void MainWindow::changernote(int i){
    if (i == 1){
        this->p->listeNotes[indicenoteachanger] = "DO";
        this->p->listeOctave[indicenoteachanger] = 3;
    }
    if (i == 2){
        this->p->listeNotes[indicenoteachanger] = "DO#";
        this->p->listeOctave[indicenoteachanger] = 3;
    }
    if (i == 3){
        this->p->listeNotes[indicenoteachanger] = "RE";
         this->p->listeOctave[indicenoteachanger] = 3;
    }
    if (i == 4){
        this->p->listeNotes[indicenoteachanger] = "RE#";
         this->p->listeOctave[indicenoteachanger] = 3;
    }
    if (i == 5){
        this->p->listeNotes[indicenoteachanger] = "MI";
        this->p->listeOctave[indicenoteachanger] = 3;
    }
    if (i == 6){
        this->p->listeNotes[indicenoteachanger] = "FA";
        this->p->listeOctave[indicenoteachanger] = 3;
    }
    if (i == 7){
        this->p->listeNotes[indicenoteachanger] = "FA#";
        this->p->listeOctave[indicenoteachanger] = 3;
    }
    if (i == 8){
        this->p->listeNotes[indicenoteachanger] = "SOL";
        this->p->listeOctave[indicenoteachanger] = 3;
    }
    if (i == 9){
        this->p->listeNotes[indicenoteachanger] = "SO#L";
        this->p->listeOctave[indicenoteachanger] = 3;
    }
    if (i == 10){
        this->p->listeNotes[indicenoteachanger] = "LA";
        this->p->listeOctave[indicenoteachanger] = 3;
    }
    if (i == 11){
        this->p->listeNotes[indicenoteachanger] = "LA#";
        this->p->listeOctave[indicenoteachanger] = 3;
    }
    if (i == 12){
        this->p->listeNotes[indicenoteachanger] = "SI";
        this->p->listeOctave[indicenoteachanger] = 3;
    }
    if (i == 13){
        this->p->listeNotes[indicenoteachanger] = "DO";
        this->p->listeOctave[indicenoteachanger] = 4;
    }
    if (i == 14){
        this->p->listeNotes[indicenoteachanger] = "DO#";
        this->p->listeOctave[indicenoteachanger] = 4;
    }
    if (i == 15){
        this->p->listeNotes[indicenoteachanger] = "RE";
        this->p->listeOctave[indicenoteachanger] = 4;
    }
    this->voirPartition();
    emit modifPartitionfaite();
}

/** @brief
 * Cette fonction met à jour les parametres de la partition de la classe partition
 * Elle appelle la fonction voirPartition pour que l'affichage se mette à jour
 */
void MainWindow::changertempo(int i){

    if (i == 1){
        this->p->listeRythme[indicenoteachanger] = "NOIRE";
    }
    if (i == 2){
        this->p->listeRythme[indicenoteachanger] = "BLANCHE";
    }
    if (i == 3){
        this->p->listeRythme[indicenoteachanger] = "RONDE";
    }
    if (i == 4){
        this->p->listeRythme[indicenoteachanger] = "CROCHE";
    }
    if (i == 5){
        this->p->listeRythme[indicenoteachanger] = "NOIRE_POINTEE";
    }
    if (i == 6){
        this->p->listeRythme[indicenoteachanger] = "BLANCHE_POINTEE";
    }

    this->voirPartition();
    emit modifPartitionfaite();

}

void MainWindow::cacherDialoguemodif(){
    this->information->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}
