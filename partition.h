#pragma once
#include <vector>
#include <unordered_map>
#include <QChar>
#include <QTextStream>
#include <time.h>
//#include "portaudio.h"
#include <stdio.h>
#include <math.h>
//#include "portaudio.h"
#define FREQUENCY 440
#define SAMPLE_RATE 44100
#define TABLE_SIZE SAMPLE_RATE
#define NUM_SECONDS 3
#define FRAMES_PER_BUFFER 256

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* for sleep() */

#include <math.h>

typedef struct _testData {
  float sine[TABLE_SIZE];
  int phase;
} TestData;

/* callback function prototype */
/*static int paCallback( const void *inputBuffer,
             void *outputBuffer, unsigned long framesPerBuffer,
             const PaStreamCallbackTimeInfo* timeInfo,
             PaStreamCallbackFlags statusFlags, void *userData );

static void joueSinusoide(int frequence, float temps) ;*/


using std::vector ;

static float nombredeDoublesCroches(float t, float tempo) ;
static bool estTriolet(int t, float tempo) ;

/* Cette classe transforme la lecture clavier de l'utilisateur en partition
 * les attributs de la classe sont :
 * listeNotes : contient les notes jouées par l'utilisateur
 * listeTemps : contient le temps qu'est jouée cette note
 */
class Partition
{
    public:
        Partition();
        void ajoutNote(char c/*,int t*/) ;
        float ajoutTemps(clock_t t) ;
        void calculDuree() ;
        void creeRythme() ;
        void jouer() ;


        virtual ~Partition();
        int lectureClavier() ;  // quand lectureClavier renvoie un 1, cela signifie que l'utilisateur a tapé '\n'
                                // c'est la fin de la partition
        int frequence(int n) ;

        // dictionnaire qui à une touche de clavier associe une note
        std::unordered_map<char,std::tuple<std::string,int>> dicco_notes ;
        std::unordered_map<float,std::string> dicco_rythme ;
    //    std::vector<std::tuple<std::string,int>> dicco_son ;
     //   std::tuple<std::tuple<std::string,int>, int> dicco_frequence ;
        std::vector<std::tuple<std::string,int>> dicco_notes2 ;
        std::vector<int> dicco_frequence ;


        float listePulsations[4] = {0} ;
        float tempo ;
        std::vector<char> listeClavier ; // stocke toutes les notes tapées au clavier sous forme de caractères 'q', 's'...
        std::vector<std::string> listeNotes ; // stocke toutes les notes tapées au clavier sous forme de notes "DO", "RE"...
        std::vector<float> listeTemps ; // stocke le temps en ms que cette note est jouée
        std::vector<int> listeDuree ;
        std::vector<int> listeOctave ;
        std::vector<std::string> listeRythme ; // stocke le rythme d'une note sous la forme "NOIRE", "BLANCHE"...

    protected:

    private:

        bool premiereValeur ; // Attention ! Il faut le réinitialiser quand on recommence un partition

};
