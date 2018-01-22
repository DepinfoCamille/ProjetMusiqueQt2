#pragma once
#include <unordered_map>
#include <vector>
#include <QChar>
#include <QTextStream>
#include <time.h>

#include <QPushButton>
#include <stdio.h>
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* for sleep() */

#include <math.h>

 void joueSinusoide(int frequence, float temps) ;

 float nombredeDoublesCroches(float t, float tempo) ;

/* Cette classe transforme la lecture clavier de l'utilisateur en partition
 * les attributs de la classe sont :
 * listeNotes : contient les notes jouées par l'utilisateur
 * listeTemps : contient le temps qu'est jouée cette note
 */
class Partition
{
    public:
        Partition();

        int setTempo( float val) ;
        void jouer() ;
        void initPartition() ;

        virtual ~Partition();

        void ajoutNote(char c) ;
        void ajoutTemps(clock_t t) ;
        void creeRythme() ;

        // stocke toutes les notes tapées au clavier sous forme de notes "DO", "RE"...
        std::vector<std::string> listeNotes ;
        // stocke les octaves des notes de listeNotes
        std::vector<int> listeOctave ;
        // stocke le rythme d'une note sous la forme "NOIRE", "BLANCHE"...
        std::vector<std::string> listeRythme ;
        //vecteur de boutons sur la position de chaque note
        std::vector<QPushButton*> listebuttons;
        // stocke la durée en ms de chaque note
        std::vector<int> listeDuree ;


    protected:

        // quand lectureClavier renvoie un 1, cela signifie que l'utilisateur a tapé sur entrée
        // c'est la fin de la partition
        int lectureClavier() ;
        void calculDuree() ;

        // Les dictionnaires sont les objets qui permettent de créer les listes
        // contenant différentes informations relatives à la partition

        // dictionnaire qui à une touche de clavier associe une note
        std::unordered_map<char,std::tuple<std::string,int>> dicco_notes ;
        // dictionnaire qui à un nombre de doubles croches associe une string de la forme "CROCHE"
        std::unordered_map<float,std::string> dicco_rythme ;
        // "dictionnaire" rangeant les notes (tuple contenant son nom et son octave) par ordre croissant

        // Les listes contiennt différentes informations relatives à la partition

        // stocke toutes les notes tapées au clavier sous forme de caractères 'q', 's'...
        std::vector<char> listeClavier ;
        // stocke le moment où l'utilisateur appuie sur chaque touche
        std::vector<float> listeTemps ;

        // Permet d'établir le tempo
        float listePulsations[4] = {0} ;
        float tempo ;


    private:

};
