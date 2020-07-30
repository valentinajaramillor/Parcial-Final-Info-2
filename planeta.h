#ifndef PLANETA_H
#define PLANETA_H


class planeta
{
public:
    planeta(float PX_, float PY_, float VX_, float VY_, float mass, float R_);
    void asignar(float PX_, float PY_, float VX_, float VY_, float AX_, float AY_);
    float getX();
    float getY();
    float getVX();
    float getVY();
    float getAX();
    float getAY();
    float getR();
    float get_mass();
    void acelerar(float px2_, float py2_, float mass2);
    void actualizar(float dt);

private:
    float PX;
    float PY;
    float masa;
    float R;
    float VX;
    float VY;
    float radio;
    float angulo;
    float AX;
    float AY;
    float G;

};

#endif // PLANETA_H
