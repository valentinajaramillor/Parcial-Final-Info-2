#ifndef PLANETAGRAF_H
#define PLANETAGRAF_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "planeta.h"


class planetagraf: public QGraphicsItem
{
public:
    planetagraf(float x, float y, float vx, float vy, float m, float r);
    ~planetagraf();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setEscala(float s);
    void actualizar(float dt);
    planeta* getEsf();

private:
    planeta* esf;
    float escala;
    bool mov;

};

#endif // PLANETAGRAF_H
