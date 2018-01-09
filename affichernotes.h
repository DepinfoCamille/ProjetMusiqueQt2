#ifndef AFICHERNOTES_H
#define AFICHERNOTES_H

#include <unordered_map>
#include <QWidget>

class Afichernotes : public QWidget
{
    Q_OBJECT
public:
    explicit Afichernotes(QWidget *parent = nullptr);


signals:

protected:
    virtual void paintEvent(QPaintEvent *event);


public slots:
};

#endif // AFICHERNOTES_H
