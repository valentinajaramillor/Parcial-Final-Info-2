#include "planeta.h"
#include <math.h>
#include <cmath>
#include <QDebug>

planeta::planeta(float PX_, float PY_, float VX_, float VY_, float mass, float R_)
{
    /* El constructor asigna los valores entregados como los atributos del planeta. También, se establece la constante
     * de gravitación como 1, y las aceleraciones iniciales como 0
     */
    PX=PX_;
    PY=PY_;
    VX=VX_;
    VY=VY_;
    masa=mass;
    AX=0;
    AY=0;
    G=1;
    R=R_;

}

void planeta::asignar(float PX_, float PY_, float VX_, float VY_, float AX_, float AY_)
{
    PX=PX_;
    PY=PY_;
    VX=VX_;
    VY=VY_;
    AX=AX_;
    AY=AY_;
}

float planeta::getX()
{
    // Método para entregar u obtener la posición en x del cuerpo
    return PX;
}

float planeta::getY()
{
    // Método para entregar u obtener la posición en y del cuerpo
    return PY;
}

float planeta::getVX()
{
    // Método para entregar u obtener la velocidad en x del cuerpo
    return VX;
}

float planeta::getVY()
{
    // Método para entregar u obtener la velocidad en y del cuerpo
    return VY;
}

float planeta::getAX()
{
    // Método para entregar u obtener la aceleración en x del cuerpo
    return AX;
}

float planeta::getAY()
{
    // Método para entregar u obtener la aceleración en y del cuerpo
    return AY;
}

float planeta::get_mass()
{
    // Método para entregar u obtener la masa del cuerpo
    return masa;
}

float planeta::getR()
{
    // Método para entregar u obtener el radio del cuerpo
    return R;
}


void planeta::acelerar(float px2_, float py2_, float mass2)
{
    /* Este método realiza el cálculo del ángulo del vector director, la distancia del planeta al sol, y las
     * aceleraciones en x y en y del cuerpo. Para esto usa los valores entregados al método, que corresponden a la
     * posición del sol y su masa
     */

    // Se inicializan los modificadores del signo de las aceleraciones en 1
    // Estos servirán para asignarle el sentido correcto a las componentes de la aceleración
    int signoAX=1;
    int signoAY=1;

    // Si el cuerpo se encuentra en el primer cuadrante...
    if ((py2_-PY)>=0 && (px2_-PX)>=0){

        // Y si se encuentra en el eje y o x del espacio, entonces se asigna el valor correcto del angulo
        // Pi para cuando se encuentra en el eje x, y Pi medios para cuando se encuentra en el eje y
        if ((py2_-PY)==0)
            angulo= M_PI;
        else if ((px2_-PX)==0)
            angulo= M_PI/2;

        // Pero si se encuentra en cualquier otro lugar del primer cuadrante, se dejan los signos de la aceleración sin
        //   cambio
        else {
            angulo =atan((py2_-PY)/(px2_-PX));
            signoAX=1;
            signoAY=1;
        }
    }

    // Se continua con el proceso de calculo del angulo y de los signos de las aceleraciones, dependiendo de a que
    //     dirección apunta el vector director de la aceleración hacia el sol
    else if ((py2_-PY)>=0 && (px2_-PX)<0){
        angulo =atan((py2_-PY)/abs(px2_-PX));
        signoAX=-1;
        signoAY=1;
    }
    else if ((py2_-PY)<0 && (px2_-PX)<0){
        angulo =atan(abs(py2_-PY)/abs(px2_-PX));
        signoAX=-1;
        signoAY=-1;
    }
    else {
        angulo =atan(abs(py2_-PY)/abs(px2_-PX));
        signoAX=1;
        signoAY=-1;
    }

    // Se calcula la distancia entre el cuerpo y el sol
    radio=pow( (pow((px2_-PX),2) + pow((py2_-PY),2)),0.5);
    // Finalmente se calculan las componentes de la aceleración con los cambios de signo
    AX= (((G*mass2)/(radio*radio))*cos(angulo))*signoAX;
    AY= (((G*mass2)/(radio*radio))*sin(angulo))*signoAY;
}

void planeta::actualizar(float dt)
{
    /* Este método calcula las velocidades del cuerpo y su posición en x y en y
     */
    VX= VX + (AX*dt);
    VY= VY + (AY*dt);
    PX= PX+ (VX*dt) + ((AX*(dt*dt))*0.5);
    PY= PY+ (VY*dt) + ((AY*(dt*dt))*0.5);

}
