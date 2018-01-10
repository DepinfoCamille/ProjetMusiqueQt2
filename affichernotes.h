#ifndef AFFICHERNOTES_H
#define AFFICHERNOTES_H

#include <unordered_map>
#include <QWidget>
#include <QPainter>

class Affichernotes : public QWidget
{
    Q_OBJECT
public:
    //Partition *p
    explicit Affichernotes(QWidget *parent = nullptr);
    void paint(QPainter *painter, QPaintEvent *event, int a);

    std::vector<std::string> listeNotes ;
    std::vector<std::string> listeTemps ;
    std::vector<int> listeOctaves ;

   /* QVector<int> listeOctaves;
    QVector<QString>listeNotes;


    QVector<QString> listeTemps;*/



signals:

protected:
    virtual void paintEvent(QPaintEvent *event);


public slots:
};

#endif // AFFICHERNOTES_H
