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

    //dessin de chaque note de ListeNotes
    for (unsigned int i=0; i<listeNotes.size(); i++){
        painter.setBrush(QBrush(Qt::NoBrush )); // pas de fond
        const char* notei= listeNotes[i].c_str();
        const char* tempsi = listeTemps[i].c_str();//transorme les std::str en char*
        int j;
        j= i/15;
        int positionx = 130 +(i-15*j)*35; //position de départ
        int positiony = 90 + j*90;

        compteur +=  valeursnotes[tempsi];

        //barres de mesure
        if (compteur== mesure || compteur == 2* mesure || compteur == 3*mesure) {
            compteur = 0;
            painter.drawLine (QPoint(positionx + 25, positiony -2 ),QPoint(positionx + 25, positiony -42));
        }
        //Les coordonnes sont pour l'octave 3, beaucoup plus courante que l'octave 4
        if (listeOctaves[i] == 4){
            positiony = positiony - 35 ;
        }
        //Localisation de la note en fonction de si c'est un DO-RE...
        if (strstr(notei, "DO")){
            positiony = positiony+2;
            if (listeOctaves[i] == 3){
            painter.drawLine(QPoint(positionx - 5 ,positiony + 5),QPoint(positionx + 15,positiony + 5));
            }
        }
        if (strstr(notei, "RE")){
            positiony = positiony - 2;
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
        //si la note est 'coloriée' en noire
        if ((strstr(tempsi,"NOIRE")) || (strstr(tempsi, "CROCHE")))  {
            painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
        }
        //élaboration de la Croche
        if (strstr(tempsi, "CROCHE")){

                    if (listeOctaves[i] == 3) {
                    painter.drawLine(QPoint(positionx +9 ,positiony - 25 ),QPoint(positionx + 16 ,positiony - 20));
                }
                if (listeOctaves[i] == 4){
                   painter.drawLine(QPoint(positionx  ,positiony +30) ,QPoint(positionx +6 ,positiony + 24));
                }
            }
        //baton des notes n'étant pas des Rondes
        if (tempsi != "RONDE"){
            if (listeOctaves[i] == 3) {
                painter.drawLine(QPoint(positionx +9 ,positiony ),QPoint(positionx + 9,positiony - 25));
            }
            if (listeOctaves[i] == 4){
               painter.drawLine(QPoint(positionx ,positiony +3 ),QPoint(positionx ,positiony + 30));
            }
         }
        //Caractères spéciaux
        if (strstr(notei, "#")){
            painter.drawLine(QPoint(positionx - 10 ,positiony -2 ),QPoint(positionx - 14 ,positiony + 10));
            painter.drawLine(QPoint(positionx - 5 ,positiony -2 ),QPoint(positionx - 9 ,positiony + 10));
            painter.drawLine(QPoint(positionx - 14 ,positiony+1),QPoint(positionx - 3 ,positiony+1));
            painter.drawLine(QPoint(positionx - 17 ,positiony+6),QPoint(positionx - 6 ,positiony+6));
        }
        if (strstr(tempsi,"POINTEE")){
            painter.drawEllipse(QRectF (positionx + 15 ,positiony,2,2));

        }
        //dessin de l'ellipse aux coordonnées correctes
         painter.drawEllipse(QRectF (positionx ,positiony,9,9));

    }
    painter.end();

}







