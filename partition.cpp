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


/** Joue une sinusoïde
 * @param frequence
 * @param temps en ms */
static void joueSinusoide(int frequence, float temps){
    PaStreamParameters  outputParameters;
    PaStream*           stream;
    PaError             err;
    paTestData          data;
    PaTime              streamOpened;
    int                 /*i,*/ totalSamps;

    int longueurTable = (int)(temps/ 1000 * SAMPLE_RATE) ;

#if TEST_UNSIGNED
    printf("PortAudio Test: output unsigned 8 bit sine wave.\n");
#else
    printf("PortAudio Test: output signed 8 bit sine wave.\n");
#endif
    /* initialise sinusoidal wavetable */
    for(int i=0; i</*longueurTable*/ TABLE_SIZE; i++ )
    {
       std::cout << i << std::endl ;
     //   data.sine[i] = /*SILENCE + */(char) (127.0 * sin((double)frequence*(double)i/(double)TABLE_SIZE * M_PI * 2.0));
        data.sine[i] = SILENCE + (float) (127.0 * sin((double)frequence*(double)i/(double)longueurTable/*TABLE_SIZE)*/ * M_PI * 2.0));
    //    std::cout << (char) (127.0 * sin((double)frequence*(double)i/(double)longueurTable/*TABLE_SIZE)*/ * M_PI * 2.0)) << std::endl ;
    }
    data.left_phase = data.right_phase = 0;
    data.framesToGo = totalSamps =  NUM_SECONDS * SAMPLE_RATE; /* Play for a few seconds. */

    err = Pa_Initialize();
  //  if( err != paNoError )
    //    goto error;

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* Default output device. */
    if (outputParameters.device == paNoDevice) {
      fprintf(stderr,"Error: No default output device.\n");
     // goto error;
    }
    outputParameters.channelCount = 2;                     /* Stereo output. */
    outputParameters.sampleFormat = TEST_FORMAT;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;
    err = Pa_OpenStream( &stream,
                         NULL,      /* No input. */
                         &outputParameters,
                         SAMPLE_RATE,
                         256,       /* Frames per buffer. */
                         paClipOff, /* We won't output out of range samples so don't bother clipping them. */
                         patestCallback,
                         &data );
 //   if( err != paNoError )
   //     goto error;

    streamOpened = Pa_GetStreamTime( stream ); /* Time in seconds when stream was opened (approx). */

    clock_t start = clock() ;
    err = Pa_StartStream( stream );
 //   if( err != paNoError )
   //     goto error;

    /* Watch until sound is halfway finished. */
    /* (Was ( Pa_StreamTime( stream ) < (totalSamps/2) ) in V18. */
  //  while( (Pa_GetStreamTime( stream ) - streamOpened) < (PaTime)NUM_SECONDS / 2.0 )
    //    Pa_Sleep(10);

    /* Stop sound. */
/*    printf("Stopping Stream.\n");
    err = Pa_StopStream( stream );
    if( err != paNoError )
        goto error;

    printf("Pause for 2 seconds.\n");
 //   Pa_Sleep( 2000 );

    printf("Starting again.\n");
    err = Pa_StartStream( stream );
    if( err != paNoError )
        goto error;

    printf("Waiting for sound to finish.\n");

    while( ( err = Pa_IsStreamActive( stream ) ) == 1 )
        Pa_Sleep(100);
    if( err < 0 )
        goto error;*/

    while(1){

        if ((clock()-start)/(float)CLOCKS_PER_SEC==temps/1000){
            std::cout << "arret" << std::endl ;
            err = Pa_CloseStream( stream );
            Pa_Terminate();
            printf("Test finished.\n");
            return ;
          //  if( err != paNoError )
            //    goto error;
        }
    }



/*error:
    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );*/
}

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

    joueSinusoide(262, 2000) ; // DO
    joueSinusoide(294 ,1000) ; // RE
    joueSinusoide(330 ,1000) ; // MI
    joueSinusoide(349 ,1000) ; // FA

 //   joueSinusoide(300,1) ;
    joueSinusoide(650,1000) ;

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
               AudioOutputStreamer* pAudioOutputStreamer = new AudioOutputStreamer(entierFrequence, this->listeDuree[i]);
          //     pAudioOutputStreamer->setFrequency(entierFrequence);
            //   pAudioOutputStreamer->setLenght(1/((this->listeTemps[i]/CLOCKS_PER_SEC)) /*100000*CLOCKS_PER_SEC/(this->listeTemps[i])*//*/100*/);
               std::cout << "On joue la fréquence " << entierFrequence << std::endl ;
               std::cout << "On attend " <<(this->listeDuree[i]) << "ms" << std::endl ;
               pAudioOutputStreamer->start();
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

