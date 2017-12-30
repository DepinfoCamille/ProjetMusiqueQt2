#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "partition.h"
#include <time.h>

#include "boitededialogue.h"

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
    BoitedeDialogue* dialogue ;
public slots:
    void affichecle();
    void ecrirePartition() ;
    void afficherTexte() ;

private:
    Ui::MainWindow *ui;
  //  void affichedo(position,ligne);

};

#endif // MAINWINDOW_H
