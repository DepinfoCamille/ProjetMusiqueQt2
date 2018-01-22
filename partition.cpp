#include "Partition.h"
#include <iostream>
#include <conio.h>
#include <math.h>
#include <fstream>
#include <QThread.h>
#include <windows.h>
#include "audiooutputstreamer.h"

#include <QChar>

/** Joue une sinusoïde
 * @param frequence
 * @param temps en ms */
void joueSinusoide(int frequence, float temps){

}

int Partition::setTempo(float val){
    int i = 0 ;
    while(this->listePulsations[i]!=0){
        i++;
    }
    if(i<4){
        this->listePulsations[i] = val;
    }

    if(i==3){
        this->tempo = (this->listePulsations[3]-this->listePulsations[0])/3 ;
    }

    return i ;
}

/** @brief Reinitialise la partition*/
void Partition::initPartition(){

    /* Initialisation du tempo*/
    for(int i = 0 ; i<4 ; i++){
        this->listePulsations[i] = 0 ;
    }

    /*Initialisation des listes contenant les informations de la partition*/
    this->listeClavier.clear() ;
    this->listeNotes.clear() ;
    this->listeTemps.clear() ;
    this->listeDuree.clear() ;
    this->listeOctave.clear() ;
    this->listeRythme.clear() ;
}

/** @param t le temps qu'est joué la note en ms
 *  @param tempo le temps que dure une pulsation en ms
 *  @return le nombre de croches contenues dans la note
 */
 float nombredeDoublesCroches(float t, float tempo){
    return ceil(4.0*/*temps*/t/tempo) ;

}

/**
 * @brief Partition::Partition crée ce qu'on a choisi d'appeler des dictionnaires
 * Un dictionnaire dicco_notes associe le caractère tapé au clavier à la note à laquelle il correspond
 * Un dictionnaire dicco_notes2 est en fait un vecteur des différentes notes par ordre croissant
 * Un dictionnaire dicco_frequence est le vecteur des différentes fréquences des notes par ordre croissant
 */
Partition::Partition(){

    this->dicco_notes = {
        {'q',std::make_tuple("DO",3)},{'z',std::make_tuple("DO#",3)},
        {'s',std::make_tuple("RE",3)}, {'e',std::make_tuple("RE#",3)},
        {'d',std::make_tuple("MI",3)}, {'f',std::make_tuple("FA",3)},
        {'g',std::make_tuple("SOL",3)}, {'y',std::make_tuple("SOL#",3)},
        {'h',std::make_tuple("LA",3)},{'u',std::make_tuple("LA#",3)},
        {'j',std::make_tuple("SI",3)}, {'k',std::make_tuple("DO",4)}, {'o',std::make_tuple("DO#",4)},
        {'l',std::make_tuple("RE",4)}
    };
    // Ce dictionnaire associe un nombre de double croches au rythme associé
    // entre CROCHE, NOIRE, NOIRE_POINTEE, BLANCHE, BLANCHE_POINTEE, RONDE
    this->dicco_rythme = {
        {1.0, "CROCHE"}, {2.0, "CROCHE"}, {3.0, "NOIRE"}, {4.0, "NOIRE"}, {5.0, "NOIRE"},
        {6.0, "NOIRE_POINTEE"} , {7.0, "NOIRE_POINTEE"},
        {8.0, "BLANCHE"}, {9.0, "BLANCHE"}, {10.0,"BLANCHE"}, {11.0,"BLANCHE"},
        {12.0,"BLANCHE_POINTEE"}, {13.0,"BLANCHE_POINTEE"}, {14.0,"BLANCHE_POINTEE"},
        {16.0, "RONDE"}, {17.0, "RONDE"}, {18.0, "RONDE"}, {19.0, "RONDE"}, {20.0, "RONDE"}
    };



}

/** cette fonction ajoute une note qui dure t ms à la partition
 * @param c le caractère entré au clavier par l'utiliateur
 */
void Partition::ajoutNote(char c){
        std::string note ;
        int octave = -1 ;

        // on associe le caractère entré à une note donnée
        std::unordered_map<char,std::tuple<std::string,int>>::iterator it;
        it = this->dicco_notes.find(c);
        if (it != this->dicco_notes.end()){
            note = std::get<0>(it->second) ;
            octave = std::get<1>(it->second) ;

        }

        // on ajoute la note à la partition
        this->listeNotes.push_back(note) ;
        this->listeOctave.push_back(octave) ;

}

/** Ajoute le temps (en ms) qu'a duré la note tapée à la partition */
void Partition::ajoutTemps(clock_t t){

    float floatT = t/(float)CLOCKS_PER_SEC ;

    if(!this->listeTemps.empty() /*&& !this->premiereValeur*/){
        float start = this->listeTemps.back() ;

        this->listeTemps.push_back(floatT) ;
    }

    else{
        this->listeTemps.push_back(floatT) ;
    }
}

/** @brief Cette fonction calcule la durée de chaque note à partir de listeTemps
 * et la stocke dans listeDuree
 * listeTemps contient les temps où l'utilisateur appuie sur chaque touche
 * listeDuree utilise listeTemps pour calculer la durée de la note
 */
void Partition::calculDuree(){

    for(std::vector<float>::iterator it = this->listeTemps.begin() ;
        it != this->listeTemps.end()-1 ; it++){
        this->listeDuree.push_back(1000*(*(it+1)-*it)) ;
    }
}

/** @brief Stocke le rythme de la partition (ex : "NOIRE", "NOIRE", "CROCHE" "CROCHE" "NOIRE")
 * dans listeRythme
 */
void Partition::creeRythme(){

    this->calculDuree() ;

    for(std::vector<int>::iterator it = this->listeDuree.begin() ;
        it != this->listeDuree.end() ; it++){

        // on stocke le rythme sous la forme "NOIRE", "CROCHE"... dans listeRythme
        std::string sRythme = this->dicco_rythme[nombredeDoublesCroches(*it, this->tempo)] ;
        this->listeRythme.push_back(sRythme) ;
    }

}


Partition::~Partition()
{
    //dtor
}

