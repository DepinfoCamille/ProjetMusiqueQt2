#include "Partition.h"
#include <iostream>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <fstream>
#include <QThread.h>
#include <windows.h>
#include "audiooutputstreamer.h"

#include <QChar>

static float nombredeDoublesCroches(int t, float tempo){
    float temps = static_cast<float>(t) ;
    std::cout << "temps " <<t << "tempo " <<tempo << std::endl ;

    std::cout << "nombre croches " << ceil(4.0*temps/tempo) << std::endl ;

    return ceil(2.0*temps/tempo) ; // En fait on est en croches

}

static bool estTriolet(int t, float tempo){
    float temps = static_cast<float>(t) ;

    return ceil(3.0*temps/tempo)==1.0 ;
}

Partition::Partition(){
//    this->listeNotes = new std::vector<char*>() ;
 //   this->listeTemps = new std::vector<int>() ;
    this->dicco_notes = {
   {'q',std::make_tuple("DO",3)},{'z',std::make_tuple("DO#",3)}, {'s',std::make_tuple("RE",3)}, {'e',std::make_tuple("RE#",3)},
       {'d',std::make_tuple("MI",3)}, {'f',std::make_tuple("FA",3)}, {'t',std::make_tuple("FA#",3)}, {'g',std::make_tuple("SOL",3)},
        {'y',std::make_tuple("SOL#",3)}, {'h',std::make_tuple("LA",3)},{'u',std::make_tuple("LA#",3)}, {'j',std::make_tuple("SI",3)},
        {'k',std::make_tuple("DO",4)}, {'o',std::make_tuple("DO#",4)}, {'l',std::make_tuple("RE",4)}};
    this->dicco_rythme = {
        {1.0, "CROCHE"}, {2.0, "NOIRE"}, {4.0, "BLANCHE"}, {3.0, "NOIRE_POINTEE"}, {8.0, "RONDE"}, {6.0,"BLANCHE_POINTEE"}
    };
  /*  this->dicco_son.push_back(std::make_tuple("DO",3)) ; this->dicco_son.push_back(std::make_tuple("DO#",3)) ;
    this->dicco_son.push_back(std::make_tuple("RE",3)) ; this->dicco_son.push_back(std::make_tuple("RE#",3)) ;
    this->dicco_son.push_back(std::make_tuple("MI",3)) ;this->dicco_son.push_back(std::make_tuple("FA",3)) ;
    this->dicco_son.push_back(std::make_tuple("FA#",3)) ; this->dicco_son.push_back(std::make_tuple("SOL",3)) ;
    this->dicco_son.push_back(std::make_tuple("SOL#",3)) ; this->dicco_son.push_back(std::make_tuple("LA",3)) ;
    this->dicco_son.push_back(std::make_tuple("LA#",3))  ;this->dicco_son.push_back(std::make_tuple("SI",3)) ;
    this->dicco_son.push_back(std::make_tuple("DO",4)) ; this->dicco_son.push_back(std::make_tuple("DO#",4))  ;
    this->dicco_son.push_back(std::make_tuple("RE",4)) ; */
    this->dicco_notes2.push_back(std::make_tuple("DO",3)) ; this->dicco_notes2.push_back(std::make_tuple("DO#",3)) ;
        this->dicco_notes2.push_back(std::make_tuple("RE",3)) ; this->dicco_notes2.push_back(std::make_tuple("RE#",3)) ;
        this->dicco_notes2.push_back(std::make_tuple("MI",3)) ;this->dicco_notes2.push_back(std::make_tuple("FA",3)) ;
        this->dicco_notes2.push_back(std::make_tuple("FA#",3)) ; this->dicco_notes2.push_back(std::make_tuple("SOL",3)) ;
        this->dicco_notes2.push_back(std::make_tuple("SOL#",3)) ; this->dicco_notes2.push_back(std::make_tuple("LA",3)) ;
        this->dicco_notes2.push_back(std::make_tuple("LA#",3))  ;this->dicco_notes2.push_back(std::make_tuple("SI",3)) ;
        this->dicco_notes2.push_back(std::make_tuple("DO",4)) ; this->dicco_notes2.push_back(std::make_tuple("DO#",4))  ;
        this->dicco_notes2.push_back(std::make_tuple("RE",4)) ;
    this->dicco_frequence.push_back(26) ; this->dicco_frequence.push_back(277 ) ;
    this->dicco_frequence.push_back(294 ) ; this->dicco_frequence.push_back(311) ;
    this->dicco_frequence.push_back(370) ; this->dicco_frequence.push_back(392) ;
    this->dicco_frequence.push_back(415) ; this->dicco_frequence.push_back(440) ;
    this->dicco_frequence.push_back(466) ; this->dicco_frequence.push_back(494) ;
    this->dicco_frequence.push_back(523) ; this->dicco_frequence.push_back(554) ;
    this->dicco_frequence.push_back(587) ; this->dicco_frequence.push_back(622) ;
    this->dicco_frequence.push_back(659) ; this->dicco_frequence.push_back(698) ;
}

/* cette fonction ajoute une note qui dure t ms à la partition */
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

/** Ajoute le temps qu'a duré la note tapée à la partition
 * Si on joue une note longue, alors nous écrivons plusieurs fois la même note
 * alors que nous ne tapons qu'une seule fois sur le clavier
 * Dans ce das, ajoutTemps renvoie 1
 * Sinon, elle renvoie 0
 */
float Partition::ajoutTemps(float t){

    if(!this->listeTemps.empty() /*&& !this->premiereValeur*/){
        float start = this->listeTemps.back() ;

        if(nombredeDoublesCroches(t-start, this->tempo)==0.0){
            t+=listeTemps.back() ;
            this->listeTemps.pop_back() ;
            this->listeTemps.push_back(t) ;
            return 1 ;
        }

        else{
            this->listeTemps.push_back(t) ;
            return 0.0 ;
        }
    }

    else{
        this->listeTemps.push_back(t) ;
        return 0.0 ;
    }
}

/** Cette fonction calcule la durée de chaque note à partir de listeTemps
 * et la stocke dans listeDuree
 * listeTemps contient en effet seulement les temps où l'utilisateur appuie sur la touche
 */
void Partition::calculDuree(){

    for(std::vector<float>::iterator it = this->listeTemps.begin() ;
        it != this->listeTemps.end()-1 ; it++){
        this->listeDuree.push_back(*(it+1)-*it) ;
        std::cout << *(it+1)+*it ;
    }
}

/** Stocke le rythme de la partition (ex : "NOIRE", "NOIRE", "CROCHE" "CROCHE" "NOIRE")
 * dans listeRythme
 */
void Partition::creeRythme(){ // Pour l'instant, on se limite aux croches

    float tempo = static_cast<float>(this->tempo) ; // temps d'une noire
    std::cout << "On a " << this->listeDuree.size() << " éléments dans notre liste temps" << std::endl ;
    float fRythme ; // contient le nombre de croches dans une note

    for(std::vector<int>::iterator it = this->listeDuree.begin() ;
        it != this->listeDuree.end() ; it++){

        fRythme = nombredeDoublesCroches(*it, tempo) ;
        std::cout <<"fRyhtme " <<fRythme << std::endl ;

        // on stocke le rythme sous la forme "NOIRE", "CROCHE"... dans listeRythme
        std::string sRythme = this->dicco_rythme[nombredeDoublesCroches(*it, tempo)] ;
        std::cout << sRythme << std::endl ;
        this->listeRythme.push_back(sRythme) ;
    }

    for(std::vector<std::string>::iterator it = this->listeRythme.begin() ;
        it != this->listeRythme.end() ; it++){
        std::cout << " " << *it ;
    }

}

/** Joue la partition
 * i.e émet un son à la durée et à la fréquence correspondant à chaques notes
 * de la partition
 */
void Partition::jouer(){

    //   vector<std::string>::iterator it;
       int entierFrequence ;
       QThread thread ;

       for(int i = 0 ; i < this->listeNotes.size() ; i++){
           entierFrequence = this->Partition::frequence(i) ;
           if(entierFrequence!=-1){
               std::cout << "on joue la note de numéro " <<entierFrequence <<std::endl ;
               AudioOutputStreamer* pAudioOutputStreamer = new AudioOutputStreamer();
               pAudioOutputStreamer->setFrequency(entierFrequence);
               pAudioOutputStreamer->setLenght(1/((this->listeTemps[i]/CLOCKS_PER_SEC)) /*100000*CLOCKS_PER_SEC/(this->listeTemps[i])*//*/100*/);
               std::cout << "On joue la fréquence" << entierFrequence << std::endl ;
               std::cout << "On attend " <<(100000*CLOCKS_PER_SEC/(this->listeTemps[i])) /*100000*CLOCKS_PER_SEC/(this->listeTemps[i])*//*/100*/ << "ms/µs" << std::endl ;
               pAudioOutputStreamer->start();
               thread.msleep ((this->listeTemps[i]/CLOCKS_PER_SEC)/100) ;
           }
       }
   }

/** Cette fonction associe une note de listeNotes à la fréquence correspondante
 */
int Partition::frequence(int n){
    int i = 0 ;

    for(std::vector<std::tuple<std::string,int>>::iterator it = this->dicco_notes2.begin() ; it != dicco_notes2.end() ; it++ ){

        if(std::get<0>(*it)==this->listeNotes[n] && std::get<1>(*it)==(this->listeOctave[n])){
            return this->dicco_frequence[i];
        }
        i++;
    }
    return -1 ; // on est sur une faute de frappe, remplacée par un silence
}

Partition::~Partition()
{
    //dtor
}

