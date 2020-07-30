#include "objeto.h"
#include "planetagraf.h"
#include "mainwindow.h"

objeto::objeto(QGraphicsItem * parent): QObject(), QGraphicsPixmapItem()
{
    dt=0.1;
    maxac=50;
    minac=2;

    int random_number1;
    random_number1 = rand() % 800 - 400;

    posx=random_number1;
    posy=300;
    setPos(posx,-posy);

    velx=0;
    vely=0;

    acy= -1*(rand() % maxac +minac);

    //draw the bullet
    setPixmap(QPixmap(":/objeto_estrella.png"));

    //connect
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this, SLOT(move()));

    timer->start(50);
}

void objeto::move()
{
    vely=vely+acy*dt;
    posx=posx+velx*dt;
    posy=posy+vely*dt+(0.5)*acy*dt*dt;

    setPos(posx,-posy);
}
