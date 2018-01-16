#pragma once
#include <vector>
#include <unordered_map>
#include <QChar>
#include <QTextStream>
#include <time.h>
#include "portaudio.h"



#define NUM_SECONDS   (8)
#define SAMPLE_RATE   (44100)
#define TABLE_SIZE    (200)
#define TEST_UNSIGNED (0)
#if TEST_UNSIGNED
#define TEST_FORMAT   paUInt8
typedef unsigned char sample_t;
#define SILENCE       ((sample_t)0x80)
#else
#define TEST_FORMAT   paInt8
typedef char          sample_t;
#define SILENCE       ((sample_t)0x00)
#endif


typedef struct
{
    int  longueurTable ;
 //   char sine[longueurTable];
    char sine[TABLE_SIZE];
    int left_phase;
    int right_phase;
    unsigned int framesToGo;
}
paTestData;

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
    char *out = (char*)outputBuffer;
    int i;
    int framesToCalc;
    int finished = 0;
    (void) inputBuffer; /* Prevent unused variable warnings. */

    if( data->framesToGo < framesPerBuffer )
    {
        framesToCalc = data->framesToGo;
        data->framesToGo = 0;
        finished = 1;
    }
    else
    {
        framesToCalc = framesPerBuffer;
        data->framesToGo -= framesPerBuffer;
    }

    for( i=0; i<framesToCalc; i++ )
    {
        *out++ = data->sine[data->left_phase];  /* left */
        *out++ = data->sine[data->right_phase];  /* right */
        data->left_phase += 1;
        if( data->left_phase >= TABLE_SIZE ) data->left_phase -= TABLE_SIZE;
        data->right_phase += 3; /* higher pitch so we can distinguish left and right. */
        if( data->right_phase >= TABLE_SIZE ) data->right_phase -= TABLE_SIZE;
    }
    /* zero remainder of final buffer */
    for( ; i<(int)framesPerBuffer; i++ )
    {
        *out++ = SILENCE; /* left */
        *out++ = SILENCE; /* right */
    }
    return finished;
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
