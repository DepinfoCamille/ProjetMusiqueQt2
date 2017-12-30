#include "Partition.h"
#include <iostream>
#include <time.h>
#include <conio.h>

#include <QChar>

Partition::Partition(){
//    this->listeNotes = new std::vector<char*>() ;
 //   this->listeTemps = new std::vector<int>() ;
    this->dicco_notes = {
   {'q',std::make_tuple("DO",3)},{'z',std::make_tuple("DO#",3)}, {'s',std::make_tuple("RE",3)}, {'e',std::make_tuple("RE#",3)},
       {'d',std::make_tuple("MI",3)}, {'f',std::make_tuple("FA",3)}, {'t',std::make_tuple("FA#",3)}, {'g',std::make_tuple("SOL",3)},
        {'y',std::make_tuple("SOL#",3)}, {'h',std::make_tuple("LA",3)},{'u',std::make_tuple("LA#",3)}, {'j',std::make_tuple("SI",3)},
        {'k',std::make_tuple("DO",4)}, {'o',std::make_tuple("DO#",4)}, {'l',std::make_tuple("RE",4)}};
}

/* cette fonction ajoute une note qui dure t ms à la partition */
void Partition::ajoutNote(char c, int t){
        std::string note ;
        int octave = -1 ;

        // on associe le caractère entré à une note donnée
        std::unordered_map<char,std::tuple<std::string,int>>::iterator it;
        // Find if an element with key exists or not.
        // find() returns an iterator
        it = this->dicco_notes.find(c);
        // Check if iterator points to end of map
        if (it != this->dicco_notes.end()){
            note = std::get<0>(it->second) ;
            octave = std::get<1>(it->second) ;

        }
        else{ // erreur de frappe
            note = "SILENCE" ;
            octave = -1 ;
        }
        // on ajoute la note à la partition
        this->listeNotes.push_back(note) ;
        this->listeOctave.push_back(octave) ;
        this->listeTemps.push_back(t) ;

}

/* cette fonction lit ce que l'utilisateur tape au clavier et le
 * sauvegarde dans listeNotes et listeTemps */
int Partition::lectureClavier(/*QTextStream notestapees*/){

 //   QObject* parent ;
 //   QProcess *process = new QProcess(parent) ;
   // QTextStream stream(stdin) ;

    clock_t start = clock(), diff;
    //char caractere = stream.padChar().toLatin1() ;

  //  char caractere = getch() ;



    /*if (caractere!='!'){

        if(caractere!=' '){
            std::cout << caractere ; // inutile, sert juste à vérifier que le programme tourne
            diff = clock() - start;
            std::cout << diff << std::endl ;
            this->Partition::ajoutNote(caractere,diff) ;
            return 0 ;
        }
    }
    else{ */
        return 1 ;
 //   }
}

Partition::~Partition()
{
    //dtor
}

