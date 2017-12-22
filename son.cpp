#include "Son.h"
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <typeinfo>

/* FONCTIONS STATIQUES*/
/* il y a 16 canaux, channel doit donc être un entier compris entre  et 15*/
/* note = 36 : do grave */
static unsigned long changer_instrument(int channel, int numinstrument)
{
    return channel | 0xC0 | (numinstrument << 8);
}

static unsigned long appuyer_touche(int channel, int note, int force)
{
    return channel | 0x90 | (note << 8) | (force << 16);
}

static unsigned long relacher_touche(int channel, int note, int force)
{
    return channel | 0x80 | (note << 8) | (force << 16);
}

Son::Son(Partition* _p){
    this->partition = _p ;
    this->dicco_son.push_back(std::make_tuple("DO",3)) ; this->dicco_son.push_back(std::make_tuple("DO#",3)) ;
    this->dicco_son.push_back(std::make_tuple("RE",3)) ; this->dicco_son.push_back(std::make_tuple("RE#",3)) ;
    this->dicco_son.push_back(std::make_tuple("MI",3)) ;this->dicco_son.push_back(std::make_tuple("FA",3)) ;
    this->dicco_son.push_back(std::make_tuple("FA#",3)) ; this->dicco_son.push_back(std::make_tuple("SOL",3)) ;
    this->dicco_son.push_back(std::make_tuple("SOL#",3)) ; this->dicco_son.push_back(std::make_tuple("LA",3)) ;
    this->dicco_son.push_back(std::make_tuple("LA#",3))  ;this->dicco_son.push_back(std::make_tuple("SI",3)) ;
    this->dicco_son.push_back(std::make_tuple("DO",4)) ; this->dicco_son.push_back(std::make_tuple("DO#",4))  ;
    this->dicco_son.push_back(std::make_tuple("RE",4)) ;
/*    this ->dicco_son = {
   {std::make_tuple<"DO",3>,48},{std::make_tuple<"DO#",3>,49}, {std::make_tuple<"RE",3>,50},/* {std::make_tuple("RE#",3),51},
       {std::make_tuple("MI",3),52}, {std::make_tuple("FA",3),53}, {std::make_tuple("FA#",3),54}, {std::make_tuple("SOL",3),55},
        {std::make_tuple("SOL#",3),56}, {std::make_tuple("LA",3),57},{std::make_tuple("LA#",3),58}, {std::make_tuple("SI",3),59},
        {std::make_tuple("DO",4),60}, {std::make_tuple("DO#",4),61}, {std::make_tuple("RE",4),62}*/
}

    //ctor
Son::~Son()
{
    //dtor
}

void Son::lecturePartition(Partition* p ) {
 //   vector<std::string>::iterator it;
    int i = 0 ;
    int entierNote ;

    for(std::vector<std::string>::iterator it = p->listeNotes.begin() ; it != p->listeNotes.end(); it++){
        entierNote = this->Son::note(i) ;
        if(entierNote!=-1){
    //        std::cout << "on joue la note de numéro " <<entierNote <<std::endl ;
/*            appuyer_touche(lphmo,entierNote,50) ;
            Sleep(p->listeTemps[i]) ;
            relacher_touche(lphmo,entierNote,50) ;*/
            i++ ;
        }
    }
}

int Son::note(int n){ // transforme la note n de la partition en un entier pouvant être lu par appuyer_touche et relacher_touche
    int i ;
    for (std::vector<std::tuple<std::string,int>>::iterator it = this->dicco_son.begin() ; it!=this->dicco_son.end() ; it++){
      /*  std::cout << "note " << std::get<0>(*it) << " " << this->partition->listeNotes[n] <<std::endl ;
        std::cout << "octave " << std::get<1>(*it) << " " << (this->partition->listeOctave[n]) <<std::endl ; */

        if(std::get<0>(*it)==this->partition->listeNotes[n] && std::get<1>(*it)==(this->partition->listeOctave[n])){
                        return i+48 ;
        }
        i++;
    }
    return -1 ; // on est sur une faute de frappe, remplacée par un silence
}



