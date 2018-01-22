#pragma once

#include <unordered_map>
#include <QWidget>
#include <QPainter>

class AfficherUneNote : public QWidget
{
    Q_OBJECT
public:
    explicit AfficherUneNote(QWidget *parent = nullptr);
    void paint(QPainter *painter, QPaintEvent *event, int a);
    std::string note ;
    int octave ;
    int i  ;


signals:

protected:
    virtual void paintEvent(QPaintEvent *event);
    std::unordered_map<std::string, float> valeursnotes = {{"NOIRE", 1.0}, {"BLANCHE", 2.0}, {"RONDE",4.0}, {"CROCHE", 0.5}, {"NOIRE_POINTEE", 1.5}, {"BLANCHE_POINTEE", 3.0}};


public slots:
};

