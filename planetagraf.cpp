#include "planetagraf.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

planetagraf::planetagraf(float x, float y, float vx, float vy, float m, float r) : escala(0.025)
{
    {
        /* El constructor crea el nuevo cuerpo y le asigna el estado de movimiento.
         * También podemos modificar la escala.
         */
        esf=new planeta(x,y,vx,vy,m,r);
        mov=true;
    }
}

planetagraf::~planetagraf()
{
    delete esf;
}

QRectF planetagraf::boundingRect() const
{
    // Se construye el rectángulo que contendrá el dibujo del cuerpo, asignándole tambien el centro de los ejes
    //    en el centro de la figura
    return QRectF(-1*escala*esf->getR(),-1*escala*esf->getR(),2*escala*esf->getR(),2*escala*esf->getR());
}

void planetagraf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Método para pintar los circulos de los cuerpos
    painter->setBrush(Qt::darkGreen);
    painter->drawEllipse(boundingRect());
}

void planetagraf::setEscala(float s)
{
    // Método para asignar una escala
    escala=s;
}

void planetagraf::actualizar(float dt)
{
    /* Este método actualiza la posición del cuerpo dentro de la escena. Para esto, primero llama los métodos de la clase "Cuerpo"
     * que calculan todos los datos necesarios para actualizar la posición del cuerpo, pero primero verificando que el cuerpo
     * si se encuentre en movimiento o no haya colisionado. Luego, mueve el cuerpo en la escena.
     * Después, se verifica si el cuerpo colisionó con otro cuerpo (usando collidingItems), y si esto sucedió,
     * se asignan los datos del cuerpo a 0, y se remueve el cuerpo de la escena, para luego cambiar el estado de movimiento a falso
     */
    if (mov==true){
        esf->actualizar(dt);
        setPos((esf->getX()*escala),(-esf->getY())*escala);
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; i++){
        if(typeid(*(colliding_items[i])) == typeid (planetagraf)){
            esf->asignar(0,0,0,0,0,0);
            scene()->removeItem(this);
            mov=false;
        }
    }
}

planeta *planetagraf::getEsf()
{
    // Método para obtener el cuerpo
    return esf;
}

