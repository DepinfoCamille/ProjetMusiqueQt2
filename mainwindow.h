#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void affichecle();

private:
    Ui::MainWindow *ui;
  //  void affichedo(position,ligne);

};

#endif // MAINWINDOW_H
