#include "Affichernotes.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <iostream>
#include "mainwindow.h"

Affichernotes::Affichernotes( QWidget *parent) : QWidget(parent)
{

}

void Affichernotes::paintEvent (QPaintEvent *event)
{

    QPainter painter(this);
    QPen myPen(Qt::black, 2, Qt::SolidLine);
    painter.setPen(myPen);
    compteur = 0.0;

    for (unsigned int i=0; i<listeNotes.size(); i++){
        painter.setBrush(QBrush(Qt::NoBrush )); // pas de fond
        const char* notei= listeNotes[i].c_str();
        const char* tempsi = listeTemps[i].c_str();//transorme les std::str en char*
        int j;
        j= i/15;

        int positionx = 130 +(i-15*j)*35; // position de départ
        int positiony = 90 + j*90;

        compteur +=  valeursnotes[tempsi];

        // Affichage des mesures
        if (compteur== mesure || compteur == 2* mesure || compteur == 3*mesure) {
            compteur = 0;
            painter.drawLine (QPoint(positionx + 25, positiony -2 ),QPoint(positionx + 25, positiony -42));
        }


        if(!this->estCledeSol){ // la position de référence est décalée
            positionx = 130 +(i-15*j)*35;
            positiony = 90 - 4*6 + j*90;
        }

        if (listeOctaves[i] == 4){
            positiony = positiony - 35 ;
        }

        if (strstr(notei, "DO")){
            positiony = positiony+2;
            // barre horizontale du do grave en clé de sol et du do aigu en clé de fa
            if (( listeOctaves[i] == 3 && this->estCledeSol) || ( listeOctaves[i] == 4 && !this->estCledeSol)){
            painter.drawLine(QPoint(positionx - 5 ,positiony + 5),QPoint(positionx + 15,positiony + 5));
            }
        }
        if (strstr(notei, "RE")){
            positiony = positiony - 2;
            // barre horizontale du ré aigu en clé de fa
            if (( listeOctaves[i] == 4 && !this->estCledeSol) ){
            painter.drawLine(QPoint(positionx - 5 ,positiony + 10),QPoint(positionx + 15,positiony + 10));
            }
        }
        if (strstr(notei, "MI")){
            positiony = positiony - 6;
        }
        if (strstr(notei, "FA")){
            positiony = positiony - 11;
        }
        if (strstr(notei, "SOL")){
            positiony = positiony - 17;
        }
        if (strstr(notei, "LA")){
            positiony = positiony - 21;
        }
        if (strstr(notei, "SI")){
           positiony = positiony - 26 ;
        }

        if ((strstr(tempsi,"NOIRE")) || (strstr(tempsi, "CROCHE")))  {
            painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
        }
        // On dessine les queues des croches
        if (strstr(tempsi, "CROCHE")){

            // barre vers le bas
            if ( positiony> 70 + j*91) {
                painter.drawLine(QPoint(positionx +9 ,positiony - 25 ),
                                 QPoint(positionx + 16 ,positiony - 20));
            }

            // barre vers le haut
            else {
            painter.drawLine(QPoint(positionx  ,positiony +30),
                             QPoint(positionx +6 ,positiony + 24));
            }
        }

        // On dessine les barre verticales des notes
        if (tempsi != "RONDE"){
            // barre vers le bas
            if (positiony>70 + j*91 ) {
                painter.drawLine(QPoint(positionx +9 ,positiony ),QPoint(positionx + 9,positiony - 25));
            }

            // barre vers le haut
            else{
               painter.drawLine(QPoint(positionx ,positiony +3 ),QPoint(positionx ,positiony + 30));
            }
         }

        // Dessin des dièses
        if (strstr(notei, "#")){
            painter.drawLine(QPoint(positionx - 10 ,positiony -2 ),QPoint(positionx - 14 ,positiony + 10));
            painter.drawLine(QPoint(positionx - 5 ,positiony -2 ),QPoint(positionx - 9 ,positiony + 10));
            painter.drawLine(QPoint(positionx - 14 ,positiony+1),QPoint(positionx - 3 ,positiony+1));
            painter.drawLine(QPoint(positionx - 17 ,positiony+6),QPoint(positionx - 6 ,positiony+6));
        }
        // Dessin des points
        if (strstr(tempsi,"POINTEE")){
            painter.drawEllipse(QRectF (positionx + 15 ,positiony,2,2));

        }
         painter.drawEllipse(QRectF (positionx ,positiony,9,9));
    }

    painter.end();
}







