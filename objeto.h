#ifndef OBJETO_H
#define OBJETO_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include <stdlib.h>

class objeto:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    objeto(QGraphicsItem * parent=0);
    float acy;
    float posx, posy, velx, vely,dt;
    int maxac;
    int minac;

public slots:
    void move();
};

#endif // OBJETO_H
