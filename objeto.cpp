#include "objeto.h"
#include "planetagraf.h"
#include "mainwindow.h"

objeto::objeto(QGraphicsItem * parent): QObject(), QGraphicsPixmapItem()
{
    g=-9.8;
    dt=0.1;
    maxvel=100;
    minvel=10;

    int random_number1;
    random_number1 = rand() % 600 -300;


    posx=random_number1;
    posy=300;
    setPos(posx,-posy);


    velx=0;
    vely= -1*(rand() % maxvel +minvel);



    //draw the bullet
    setPixmap(QPixmap(":/objeto_estrella.png"));

    //connect
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this, SLOT(move()));

    timer->start(50);
}

void objeto::move()
{
    vely=vely+g*dt;
    posx=posx+velx*dt;
    posy=posy+vely*dt+(0.5)*g*dt*dt;

    setPos(posx,-posy);

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; i++){
        if(typeid(*(colliding_items[i])) == typeid (planetagraf)){

            //remove the both
            scene()->removeItem(this);
            //delete both
            delete this;
        }
    }

//    if(pos().y() + pixmap().height() < 0){
//        scene()->removeItem(this);
//        delete this;
//    }
}
