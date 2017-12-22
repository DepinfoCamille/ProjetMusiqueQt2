#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *pic = new QWidget(this);
    pic->setStyleSheet("background-image: url(C:/Users/User/Desktop/2A/C++/5lignes.png)");
    pic->setGeometry(QRect(30,30,300,370));
    ui->CLE->addItem("Cle de Sol");
    ui->CLE->addItem("Cle de Fa");
    QObject::connect(ui->CLE, SIGNAL(currentIndexChanged(int)), this,
                     SLOT(affichecle()));


}

void MainWindow::affichecle()
{
    int cle = ui->CLE->currentIndex();
    if (cle == 0 ){
        QWidget *pic1 = new QWidget(this);
        pic1->setStyleSheet("background-image: url(C:/Users/User/Desktop/2A/C++/cledesol.png)");
       // pic1->setGeometry(QRect(30,30,400,400));
        pic1->resize(300,300);
        //pic1 ->sizeHint(Qsize())
        //pic1->sizeHint(QSize(300,300));
        pic1->adjustSize();
        pic1->show();
        pic1->setVisible(true);
        std::cout << "Cle de Sol"<<this << std::endl;
        //return 55;
    }
    if (cle == 1){
        std::cout << "Cle de fa" << std::endl;
    }



}

MainWindow::~MainWindow()
{
    delete ui;
}
