#include "ecouterpartition.h"
#include <iostream>

EcouterPartition::EcouterPartition(Partition* p)
{
    // Emplacement des fichiers wav

    char *path=nullptr ;
    size_t size = 0 ;
    path=GetCurrentDir(path,size);

    char* repWav = (char*) malloc(sizeof(char)*(strlen(path)+31)) ;
    strcpy(repWav,path) ;
    strcat(repWav,"\\..\\ProjetMusiqueQt2\\") ;

    // Remplissage des données de EcouterPartition

    this->indicePartition = 0 ;
    this->notesPartitions = new QMediaPlaylist() ;
    float temps ;

    for(unsigned int i = 0 ; i<p->listeNotes.size() ; i++){

        char* cheminNote = (char*)malloc(sizeof(char)*strlen(repWav)+10) ;
        char* nomNote = (char*) malloc(sizeof(char)*8) ;

        strcpy(nomNote, p->listeNotes[i].c_str()) ;

        char* octave = (char*) malloc(sizeof(char*));
        sprintf(octave, "%d", p->listeOctave[i]);

        strcat(nomNote,octave);
        strcat(nomNote, ".wav") ;


        strcpy(cheminNote,repWav);
        strcat(cheminNote,nomNote) ;
        std::cout << "chemin de la note jouée " << cheminNote ;

        QTimer* timer = new QTimer(this);
        connect( timer, SIGNAL( timeout() ), this, SLOT( finNote() ) );



        if(i!=0){
           temps = p->listeDuree[i]+this->listeDurees.back();
        }
        else{
            temps = p->listeDuree[i] ;
        }

        std::cout << " temps " << temps << std::endl ;

     //   this->notesPartitions->addMedia(QUrl::fromLocalFile(nomNote));
        this->notesPartitions->addMedia(QUrl(cheminNote));
        std::cout << " on passe addmedia\n" ;
        this->listeTimers.push_back(timer) ;
        this->listeDurees.push_back(temps) ;
    }

}

void EcouterPartition::joueMorceau() {

    this->player = new QMediaPlayer() ;
    this->player->setPlaylist(this->notesPartitions) ;
    this->player->play() ;

    for(unsigned int i = 0 ; i<this->listeTimers.size() ; i++){
        this->listeTimers[i]->start(this->listeDurees[i]);
     }
}


void EcouterPartition::finNote(){

    this->listeTimers[this->indicePartition]->stop() ;
    this->notesPartitions->setCurrentIndex(++this->indicePartition);
    std::cout << "indice partition " << this->indicePartition << " taille timers " << this->listeTimers.size() ;
    if(this->indicePartition>=(int)this->listeTimers.size()){
        this->player->stop() ;
    }
}

EcouterPartition::~EcouterPartition(){

    this->listeTimers.clear();
    this->listeDurees.clear() ;
}

