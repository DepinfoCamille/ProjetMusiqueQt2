#include "Afficherunenote.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <iostream>
#include "mainwindow.h"

AfficherUneNote::AfficherUneNote( QWidget *parent) : QWidget(parent)
{

}

void AfficherUneNote::paintEvent (QPaintEvent *event)
{

    QPainter painter(this);
    QPen myPen(Qt::black, 2, Qt::SolidLine);
    painter.setPen(myPen);
    const char* noteStr= this->note.c_str();

    int positionx = 130 +(i-15*j)*35; // position de départ
    int positiony = 90 + j*90;

    if(!this->estCledeSol){ // la position de référence est décalée
        positionx = 130 +(i-15*j)*35;
        positiony = 90 - 4*6 + j*90;
    }

    if (octave == 4){
        positiony = positiony - 35 ;
    }

    if (strstr(noteStr, "DO")){
        positiony = positiony+2;
        // barre horizontale du do grave en clé de sol et du do aigu en clé de fa
        if (( this->octave == 3 && this->estCledeSol) || ( this->octave == 4 && !this->estCledeSol)){
        painter.drawLine(QPoint(positionx - 5 ,positiony + 5),QPoint(positionx + 15,positiony + 5));
        }
    }
    if (strstr(noteStr, "RE")){
        positiony = positiony - 2;
        // barre horizontale du ré aigu en clé de fa
        if (( this->octave == 4 && !this->estCledeSol) ){
            painter.drawLine(QPoint(positionx - 5 ,positiony + 10),QPoint(positionx + 15,positiony + 10));
        }
    }
    if (strstr(noteStr, "MI")){
        positiony = positiony - 6;
    }
    if (strstr(noteStr, "FA")){
        positiony = positiony - 11;
    }
    if (strstr(noteStr, "SOL")){
        positiony = positiony - 17;
    }
    if (strstr(noteStr, "LA")){
        positiony = positiony - 21;
    }
    if (strstr(noteStr, "SI")){
       positiony = positiony - 26 ;
    }

    // Dessin des dièses
    if (strstr(noteStr, "#")){
        painter.drawLine(QPoint(positionx - 10 ,positiony -2 ),QPoint(positionx - 14 ,positiony + 10));
        painter.drawLine(QPoint(positionx - 5 ,positiony -2 ),QPoint(positionx - 9 ,positiony + 10));
        painter.drawLine(QPoint(positionx - 14 ,positiony+1),QPoint(positionx - 3 ,positiony+1));
        painter.drawLine(QPoint(positionx - 17 ,positiony+6),QPoint(positionx - 6 ,positiony+6));
    }
    painter.drawEllipse(QRectF (positionx ,positiony,9,9));
    painter.end();
}







