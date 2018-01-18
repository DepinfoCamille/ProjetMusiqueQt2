#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QSound>
#include "partition.h"
#include "affichernotes.h"
#include <time.h>
#include <math.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Partition* p ;
    QSound* lecture ;
    Affichernotes* an;

public slots:

    /* Slots d'affichage*/
    void affichecle();
    void afficherTempo() ;
    void affichemesure();
    void afficherCreationPartition() ;
    void afficherEcouterPartition() ;
    void voirPartition();
    void positioncurseur();

    /* Slots agissant sur la partition */
    void choisirTempo() ;
    void ecrirePartition() ;
    void ecouterPartition() ;


signals:
    void tempoDefini() ;
    void partitionEcrite() ;

private:
    Ui::MainWindow *ui;
  //  void affichedo(position,ligne);

};

#endif // MAINWINDOW_H
