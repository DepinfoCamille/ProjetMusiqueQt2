#ifndef ECOUTERPARTITION_H
#define ECOUTERPARTITION_H

#include <QAudioFormat>
#include <QAudio>
#include <QFile>
#include <QThread>
#include <QSound>
#include <QTimer>
#include "partition.h"
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <string>

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif


//QSound initQSound(char*);

class EcouterPartition : public QObject
{
    Q_OBJECT

public:
    EcouterPartition(Partition* p);
    ~EcouterPartition() ;
    std::vector<QTimer*> listeTimers  ;
    std::vector<float> listeDurees ;
    std::vector<char*> listeChemins ;
    QMediaPlaylist *notesPartitions ;
    QMediaPlayer *player ;

    int indicePartition ;

    void joueMorceau() ;


public slots:
    void finNote() ;

};

#endif // ECOUTERPARTITION_H
