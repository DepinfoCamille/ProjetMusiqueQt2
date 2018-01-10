#include "audiooutputstreamer.h"
#include <QThread>

/**
 * @brief AudioOutputStreamer::AudioOutputStreamer
 * @param duree est la longueur de la note en ms
 * @param frequence est la fréquence à laquelle la note sera jouée
 */
AudioOutputStreamer::AudioOutputStreamer(int duree, int frequence)
{
    /* Mise en place du format */

    this->_samplingRate = 44100;
    this->format.setSampleRate(_samplingRate);
    this->format.setCodec("audio/pcm");
    this->format.setByteOrder(QAudioFormat::LittleEndian);
    this->format.setSampleType(QAudioFormat::SignedInt);
    this->format.setSampleSize(8) ;

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    std::cout << "setSampleSize ok : " << std::endl ;

    if (!info.isFormatSupported(format)) {
    qWarning()<<"default format not supported try to use nearest";
    this->format = info.nearestFormat(format);
    }
    if (!info.isFormatSupported(format)) {
        qWarning()<<"nearest format not supported try to use something else";
    }

    /* Mise en place du fichier audio */

    _audio = new QAudioOutput(format, this);
    std::cout << "new audio ok : "  << std::endl ;
    _audio->setBufferSize(this->format.bytesForDuration(duree));// en bytes
    _audio->setNotifyInterval(duree);

    /* Choix du son */
    _omega = 2*M_PI*frequence;
    _amplitude = 10.;
    _delta_t = 1/_samplingRate;

    _IDWrittenSample = 0;
    _sizeNolBuffer = 0;

}

AudioOutputStreamer::~AudioOutputStreamer()
{
}

void AudioOutputStreamer::setFrequency(int f){
    _omega = 2*M_PI*f ;
}

void AudioOutputStreamer::setLenght(int l){

    // NOUVEAU TEST
    /*  _delta_t = l ;
      _samplingRate = 1/_delta_t ;*/
 //   _audio->setNotifyInterval(l);
}

void AudioOutputStreamer::start()
{
    QThread thread ;
    QObject::connect(_audio, SIGNAL(notify()), this, SLOT(slot_writeMoreData()));

    _pAudioIOBuffer = _audio->start();

    unsigned int periodSize = this->_audio->periodSize();
    this->_sizeNolBuffer = periodSize;
    this->_buffer = (signed char*) calloc(_sizeNolBuffer, sizeof(signed char));

    emit _audio->notify() ;
}


void AudioOutputStreamer::slot_writeMoreData()
{
    int nbBytes = this->_audio->bytesFree();

    if (nbBytes>0) {

        if (this->_sizeNolBuffer<nbBytes) {
            delete[] this->_buffer;
            this->_sizeNolBuffer = nbBytes;
            _buffer = (signed char*) calloc(_sizeNolBuffer, sizeof(signed char));
        }

        short int value = 0;
        for (unsigned int IDSample=0; IDSample<nbBytes; ++IDSample) {

            float time = (float)this->_IDWrittenSample * _delta_t;
            value = (signed char) (_amplitude*(float)(sin(_omega*time)));
            this->_buffer[IDSample] = value;
            ++this->_IDWrittenSample;
        }

        int nbWrittenBytes = _pAudioIOBuffer->write((const char*) _buffer, nbBytes);

        if (_IDWrittenSample>_samplingRate) {
            QObject::disconnect(_audio, SIGNAL(notify()), this, SLOT(slot_writeMoreData()));
            _audio->stop();
        }
    }
}
