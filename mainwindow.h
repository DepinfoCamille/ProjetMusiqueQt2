#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include <QSound>
#include "partition.h"
#include "affichernotes.h"
#include <time.h>
#include <math.h>
#include <QLabel>

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

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
    QLabel* information ; // = new QLabel(this) ;

protected slots:

    /* Slot d'initialisation */

    void initialisation() ;

    /* Slots d'affichage*/
    void affichecle();
    void choixmesure();
    void afficherCreationPartition() ;
    void afficherEcouterPartition() ;
    void voirPartition();
    void afficherboxmesure();
    void affichercaracteristiquesnote() ;
    void cacherDialoguemodif() ;

    /* Slots agissant sur la partition */
    void choisirTempo() ;
    void ecrirePartition() ;
    void ecouterPartition() ;
    void changerPartition();
    void changernote(int i);
    void changertempo(int i);

signals:
    void initFaite() ;
    void mesureDefinie() ;
    void tempoDefini() ;
    void partitionEcrite() ;
    void modifPartitionfaite() ;

protected:
    std::vector<QLabel*> clesDebutLignes ;

    int indicenoteachanger ;
    std::vector<QLabel*> mesureDebutLignes ;


private:
    Ui::MainWindow *ui;
  //  void affichedo(position,ligne);

};
