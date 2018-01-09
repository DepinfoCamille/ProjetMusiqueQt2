#ifndef AUDIOOUTPUTSTREAMER_H
#define AUDIOOUTPUTSTREAMER_H

#include <QObject>
#include <QAudioOutput>
#include <QAudioFormat>
#include <QIODevice>
#include <QAudioDeviceInfo>
#include <QDebug>

#include <math.h>
#include <iostream>
#include "partition.h"

using namespace std;

class AudioOutputStreamer : public QObject
{
    Q_OBJECT

    public:
        AudioOutputStreamer(int duree, int frequence);
        ~AudioOutputStreamer();
        void setNotes(Partition* p);
        void setFrequency(int f) ;
        void setLenght(int l) ;
        void start();

    public slots:
        void slot_writeMoreData();

    private:
        QAudioOutput* _audio;
        QIODevice* _pAudioIOBuffer;

        float _samplingRate;

        unsigned long _IDWrittenSample;
        float _amplitude;
        float _delta_t;
        float _omega;
        signed char* _buffer;
        int _sizeNolBuffer;
        QAudioFormat format;


};

#endif
