#pragma once
#include <vector>
#include <unordered_map>
#include <QChar>
#include <QTextStream>
#include <time.h>
#include "portaudio.h"
#include <stdio.h>
#include <math.h>
#include "portaudio.h"

#define OUTPUT_DEVICE       (Pa_GetDefaultOutputDevice())
#define SAMPLE_RATE         (44100)
#define FRAMES_PER_BUFFER   (64)

#define MIN_FREQ            (100.0f)
#define CalcPhaseIncrement(freq)  ((freq)/SAMPLE_RATE)
#ifndef M_PI
#define M_PI  (3.14159265)
#endif
#define TABLE_SIZE   (400)

typedef struct
{
    float sine[TABLE_SIZE + 1]; /* add one for guard point for interpolation */
    float phase_increment;
    float left_phase;
    float right_phase;
}
paTestData;

/* Convert phase between and 1.0 to sine value
 * using linear interpolation.
 */
float LookupSine(paTestData *data, float phase ){
    float fIndex = phase*TABLE_SIZE;
    int   index = (int) fIndex;
    float fract = fIndex - index;
    float lo = data->sine[index];
    float hi = data->sine[index+1];
    float val = lo + fract*(hi-lo);
    return val;
}

/* This routine will be called by the PortAudio engine when audio is needed.
** It may called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
static int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    paTestData *data = (paTestData*)userData;
    float *out = (float*)outputBuffer;
    int i;

    (void) inputBuffer; /* Prevent unused variable warning. */

    for( i=0; i<framesPerBuffer; i++ )
    {
        *out++ = LookupSine(data, data->left_phase);  /* left */
        *out++ = LookupSine(data, data->right_phase);  /* right */
        data->left_phase += data->phase_increment;
        if( data->left_phase >= 1.0f ) data->left_phase -= 1.0f;
        data->right_phase += (data->phase_increment * 1.5f); /* fifth above */
        if( data->right_phase >= 1.0f ) data->right_phase -= 1.0f;
    }
    return 0;
}


static void joueSinusoide(int frequence, float temps) ;


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
