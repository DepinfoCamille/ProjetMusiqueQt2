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


QSound initQSound(char*);

class EcouterPartition : public QObject
{
    Q_OBJECT

public:
    EcouterPartition(/*Partition* p*/);
    ~EcouterPartition() ;
  //  std::vector<QSound> listeSons ;
    std::vector<QTimer*> listeTimers  ;
    std::vector<int> listeDurees ;
  //  QSound son ;
    QMediaPlaylist *notesPartitions ;
    QMediaPlayer *player ;

    int indicePartition ;

    void joueMorceau() ;


public slots:

    void finNote() ;



};

#endif // ECOUTERPARTITION_H
