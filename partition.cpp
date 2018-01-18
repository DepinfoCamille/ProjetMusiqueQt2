#include "Partition.h"
#include <iostream>
#include <conio.h>
#include <math.h>
#include <fstream>
#include <QThread.h>
#include <windows.h>
#include "audiooutputstreamer.h"

#include <QChar>

//data.sine[i] = SILENCE + (char) (127.0 * sin( frequence*((double)i/(double)TABLE_SIZE) * M_PI * 2. ));
/*static int paCallback( const void *inputBuffer,
             void *outputBuffer, unsigned long framesPerBuffer,
             const PaStreamCallbackTimeInfo* timeInfo,
             PaStreamCallbackFlags statusFlags, void *userData )
{
  TestData *data = (TestData*) userData;
  float *out = (float*) outputBuffer;
  float sample;
  int i;

  for (i = 0; i < framesPerBuffer; i++) {
    sample = data->sine[data->phase++];
    *out++ = sample; /* left */
    //*out++ = sample; /* right */
/*
    if (data->phase >= TABLE_SIZE)
      data->phase -= TABLE_SIZE;
  }
  return paContinue;
}


/** Joue une sinusoïde
 * @param frequence
 * @param temps en ms */
/*static void joueSinusoide(int frequence, float temps){
    TestData data;
    PaStream *stream;
    PaStreamParameters outputParameters;
    PaError err;

    int i;
    double t;

    /* Generate table with sine values at given frequency */
   /* for (i = 0; i < TABLE_SIZE; i++) {
      t = (double)i/(double)SAMPLE_RATE;
      data.sine[i] = sin(2 * M_PI * frequence * t);
    }

    /* Initialize user data */
    /*data.phase = 0;

    /* Initialize PortAudio */
    /*Pa_Initialize();

    /* Set output stream parameters */
   /*outputParameters.device = Pa_GetDefaultOutputDevice();
    outputParameters.channelCount = 2;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency =
      Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    /* Open audio stream */
   // err = Pa_OpenStream( &stream, NULL /* no input */,
     /*            &outputParameters,
                 SAMPLE_RATE, FRAMES_PER_BUFFER, paNoFlag,
                 paCallback, &data );

    if (err != paNoError) {
      printf("PortAudio error: open stream: %s\n", Pa_GetErrorText(err));
    }

    /* Start audio stream */
  /*  err = Pa_StartStream( stream );
    if (err != paNoError) {
      printf(  "PortAudio error: start stream: %s\n", Pa_GetErrorText(err));
    }

    /* Play sine wav */
  /*  printf("Play for %d seconds.\n", temps/1000 );
    sleep(temps/1000);
    err = Pa_StopStream( stream );


    /* Stop audio stream */
  /*  if (err != paNoError) {
      printf(  "PortAudio error: stop stream: %s\n", Pa_GetErrorText(err));
    }
    /* Close audio stream */
  /*  err = Pa_CloseStream(stream);
    if (err != paNoError) {
      printf("PortAudio error: close stream: %s\n", Pa_GetErrorText(err));
    }
    /* Terminate audio stream */
   /* err = Pa_Terminate();
    if (err != paNoError) {
      printf("PortAudio error: terminate: %s\n", Pa_GetErrorText(err));
    }
}*/

/** @param t le temps qu'est joué la note en ms
 *  @param tempo le temps que dure une pulsation en ms
 *  @return le nombre de croches contenues dans la note
 */
static float nombredeDoublesCroches(float t, float tempo){
  //  float temps = static_cast<float>(t) ;
    std::cout << "temps " << t << " tempo " <<tempo << std::endl ;

    std::cout << "nombre croches " << ceil(2.0*/*temps*/t/tempo) << std::endl ;

    return ceil(2.0*/*temps*/t/tempo) ; // En fait on est en croches

}

static bool estTriolet(int t, float tempo){
    float temps = static_cast<float>(t) ;

    return ceil(3.0*temps/tempo)==1.0 ;
}

Partition::Partition(){

/*    joueSinusoide(262, 2000) ; // DO
    joueSinusoide(294 ,1000) ; // RE
    joueSinusoide(330 ,1000) ; // MI
    joueSinusoide(349 ,1000) ; // FA

 //   joueSinusoide(300,1) ;
    joueSinusoide(650,1000) ;*/

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
    this->dicco_frequence.push_back(264) ; this->dicco_frequence.push_back(277 ) ;
    this->dicco_frequence.push_back(294 ) ; this->dicco_frequence.push_back(311) ;
    this->dicco_frequence.push_back(330) ; this->dicco_frequence.push_back(349) ;
    this->dicco_frequence.push_back(370) ; this->dicco_frequence.push_back(392) ;
    this->dicco_frequence.push_back(415) ; this->dicco_frequence.push_back(440) ;
    this->dicco_frequence.push_back(466) ; this->dicco_frequence.push_back(494) ;
    this->dicco_frequence.push_back(523) ; this->dicco_frequence.push_back(554) ;
    this->dicco_frequence.push_back(587) ; this->dicco_frequence.push_back(622) ;
    this->dicco_frequence.push_back(659) ; this->dicco_frequence.push_back(698) ;
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

/** Ajoute le temps (en ms) qu'a duré la note tapée à la partition
 * Si on joue une note longue, alors nous écrivons plusieurs fois la même note
 * alors que nous ne tapons qu'une seule fois sur le clavier
 * Dans ce das, ajoutTemps renvoie 1
 * Sinon, elle renvoie 0
 */
float Partition::ajoutTemps(clock_t t){

    float floatT = t/(float)CLOCKS_PER_SEC ;

    if(!this->listeTemps.empty() /*&& !this->premiereValeur*/){
        float start = this->listeTemps.back() ;

   // ATTENTION J'ENLEVE LES TEMPS LONGS, ET JE VAIS ESSAYER DE FAIRE UNE NOUVELLE CLASSE QUI ENLEVE
   // L'ECRITURE DE PLEINS DE LETTRES A LA SUITE LORSQU'ON RESTE APPUYE
   /*     if(nombredeDoublesCroches(floatT-start, this->tempo)==0.0){

            std::cout << "On considère qu'on a un temps long" << std::endl ;

            floatT+=listeTemps.back() ;
            this->listeTemps.pop_back() ;
            this->listeTemps.push_back(floatT) ;
            return 1 ;
        }

        else{ */
            this->listeTemps.push_back(floatT) ;
            std::cout << "Temps entré dans ajoutTemps : " << floatT << std::endl ;
            return 0.0 ;
  //      }
    }

    else{
        this->listeTemps.push_back(floatT) ;
        return 0.0 ;
    }
}

/** @brief Cette fonction calcule la durée de chaque note à partir de listeTemps
 * et la stocke dans listeDuree
 * listeTemps contient en effet seulement les temps où l'utilisateur appuie sur la touche
 */
void Partition::calculDuree(){

    for(std::vector<float>::iterator it = this->listeTemps.begin() ;
        it != this->listeTemps.end()-1 ; it++){
        this->listeDuree.push_back(1000*(*(it+1)-*it)) ;
        std::cout << " Durée calculée dans calculDuree : " << 1000*(*(it+1)-*it) << std::endl ;
    }
}

/** @brief Stocke le rythme de la partition (ex : "NOIRE", "NOIRE", "CROCHE" "CROCHE" "NOIRE")
 * dans listeRythme
 */
void Partition::creeRythme(){ // Pour l'instant, on se limite aux croches

 //   float tempo = static_cast<float>(this->tempo) ; // temps d'une noire
    std::cout << "On a " << this->listeDuree.size() << " éléments dans notre liste temps" << std::endl ;
    float fRythme ; // contient le nombre de croches dans une note

    for(std::vector<int>::iterator it = this->listeDuree.begin() ;
        it != this->listeDuree.end() ; it++){

        fRythme = nombredeDoublesCroches(*it, this->tempo) ;
        std::cout <<"fRyhtme " <<fRythme << std::endl ;

        // on stocke le rythme sous la forme "NOIRE", "CROCHE"... dans listeRythme
        std::string sRythme = this->dicco_rythme[nombredeDoublesCroches(*it, this->tempo)] ;
        std::cout << sRythme << std::endl ;
        this->listeRythme.push_back(sRythme) ;
    }

    for(std::vector<std::string>::iterator it = this->listeRythme.begin() ;
        it != this->listeRythme.end() ; it++){
        std::cout << " " << *it ;
    }

}

/** @brief Joue la partition
 * i.e émet un son à la durée (en ms) et à la fréquence correspondant à chaques notes
 * de la partition
 */
void Partition::jouer(){

       int entierFrequence ;
       QThread thread ;

       for(int i = 0 ; i < this->listeNotes.size() ; i++){

           entierFrequence = this->Partition::frequence(i) ;

           if(entierFrequence!=-1){
               std::cout << "on joue la note de numéro " <<entierFrequence <<std::endl ;
               std::cout << "On joue la fréquence " << entierFrequence << std::endl ;
               std::cout << "On attend " <<(this->listeDuree[i]) << "ms" << std::endl ;
               //joueSinusoide(entierFrequence, this->listeDuree[i]) ;
               thread.msleep (this->listeDuree[i]) ;
           }
       }
   }

/** @brief Cette fonction associe une note de listeNotes à la fréquence correspondante
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

