#include "Affichernotes.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <iostream>
#include "mainwindow.h"

Afichernotes::Afichernotes(QWidget *parent) : QWidget(parent)
{
}

void Afichernotes::paintEvent(QPaintEvent *)
{
    //MainWindow w; //lerreur vient dici, ca se réinitialise

    std::unordered_map<std::string, int> valeursnotes = {{"NOIRE", 1}, {"BLANCHE", 2}, {"RONDE",4}, {"CORCHE", 0.5}};

  //  if (mesure != 0){
        //std::cout <<mesure<<"hey";
    //}

    QVector<QString> listeNotes;
    listeNotes << "RE#" << "RE" << "DO" << "RE#" <<"DO" << "MI" << "MI";

    QVector<int> listeOctaves;
    listeOctaves << 3 << 4 << 3 <<3<< 3 << 3 << 4 ;

    QVector<QString> listeTemps;
    listeTemps << "BLANCHE" <<"CORCHE" << "BLANCHE"  << "NOIRE"  << "CORCHE"  << "RONDE"  << "BLANCHE" ;

    QPainter painter(this);
    QPen myPen(Qt::black, 2, Qt::SolidLine);
    painter.setPen(myPen);

    for (int i=0; i<listeNotes.size(); i++){
        painter.setBrush(QBrush(Qt::NoBrush )); // pas de fond
        const char* notei= listeNotes[i].toStdString().data(); //transorme le QString en char*

        int positionx = 130; //position de départ
        int positiony = 90;

        if (listeOctaves[i] == 4){
            positiony = positiony - 35 ;
        }

        if (strstr(notei, "DO")){
            positionx = positionx + i*35;
            positiony = positiony+2;
            if (listeOctaves[i] == 3){
            painter.drawLine(QPoint(positionx - 5 ,positiony + 5),QPoint(positionx + 15,positiony + 5));
            }
        }
        if (strstr(notei, "RE")){
            positionx = positionx + i*35 ;
            positiony = positiony - 2;
        }
        if (strstr(notei, "MI")){
            positionx = positionx + i*35;
            positiony = positiony - 6;
        }
        if (strstr(notei, "FA")){
            positionx = positionx + i*35;
            positiony = positiony - 11;
        }
        if (strstr(notei, "SOL")){
            positionx = positionx + i*35;
            positiony = positiony - 17;
        }
        if (strstr(notei, "LA")){
            positionx = positionx + i*35;
            positiony = positiony - 21;
        }
        if (strstr(notei, "SI")){
           positionx = positionx + i*35;
           positiony = positiony - 26 ;
        }
        if ((listeTemps[i] == "NOIRE") || (listeTemps[i] == "CORCHE"))  {
            painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
        }
        if (listeTemps[i] == "CORCHE"){
            int j = 0;
            while (listeTemps[i+j] == "CORCHE"){
                j = j + 1;
            }
            if ((j == 1)) //|| (j==2 && listeOctaves[i] != listeOctaves[i+1]))     // la corche est toute seule ou ils appartiennent à des octaves différents (plus facile à coder)
                {
                    if (listeOctaves[i] == 3) {
                    painter.drawLine(QPoint(positionx +9 ,positiony - 25 ),QPoint(positionx + 16 ,positiony - 20));
                }
                if (listeOctaves[i] == 4){
                   painter.drawLine(QPoint(positionx  ,positiony +30) ,QPoint(positionx +6 ,positiony + 24));
                }
            }
            // COmpliqué à les relier pq je dois connaitre la note suivante...
            //if (j == 2) { // deux corches liées
            //    if (listeOctaves[i] == 3) {
            //        painter.drawLine(QPoint(positionx +9 ,positiony - 25 ),QPoint(positionx + 44 ,positiony - 25));
            //    }
            //    if (listeOctaves[i] == 4){
            //       painter.drawLine(QPoint(positionx  ,positiony +30) ,QPoint(positionx +6 ,positiony + 24));
            //    }
            //}

        }
        if (listeTemps[i] != "RONDE"){
            if (listeOctaves[i] == 3) {
                painter.drawLine(QPoint(positionx +9 ,positiony ),QPoint(positionx + 9,positiony - 25));
            }
            if (listeOctaves[i] == 4){
               painter.drawLine(QPoint(positionx ,positiony +3 ),QPoint(positionx ,positiony + 30));
            }
         }
        if (strstr(notei, "#")){
            painter.drawLine(QPoint(positionx - 10 ,positiony -2 ),QPoint(positionx - 14 ,positiony + 10));
            painter.drawLine(QPoint(positionx - 5 ,positiony -2 ),QPoint(positionx - 9 ,positiony + 10));
            painter.drawLine(QPoint(positionx - 14 ,positiony+1),QPoint(positionx - 3 ,positiony+1));
            painter.drawLine(QPoint(positionx - 17 ,positiony+6),QPoint(positionx - 6 ,positiony+6));
        }
       // if (strstr(notei, "_POINTEE"))
         painter.drawEllipse(QRectF (positionx ,positiony,9,9));
    }
}
