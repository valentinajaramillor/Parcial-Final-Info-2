#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <string>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dt=1;  // Se asigna el cambio en el tiempo (delta del tiempo)

    // Se asignan los limites visibles del "universo"
    h_limit=2000;
    v_limit=1000;

    tiempo=0; // Inicializo la variable con el tiempo transcurrido

    // Se inicializa el timer y la escena
    timer=new QTimer(this);
    scene=new QGraphicsScene(this);

    // La escena tiene la modificacion de los ejes, para que el punto 0,0 quede en la mitad
    scene->setSceneRect(-h_limit/2,-v_limit/2,h_limit,v_limit);

    ui->graphicsView->setScene(scene);
    ui->centralwidget->adjustSize();

    timer->stop();
    // Se realiza la conexion del timer con el metodo para actualizar las posiciones
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));

    cuerpos.append(new planetagraf(0, 0, 0, 0, 50000, 200));
    cuerpos.append(new planetagraf(-5000, 0, 0, -2, 70, 70));
    cuerpos.append(new planetagraf( 5000, 0, 0, 2, 70, 70));
    cuerpos.append(new planetagraf(0, -5000, 2, 0, 70, 70));
    cuerpos.append(new planetagraf(0,  5000, -2, 0, 70, 70));

    // Por cada cuerpo en la lista de cuerpos, se crea la opcion en el combobox, se actualiza su posicion y se agrega
    //    el cuerpo a la escena
    for(int i=0;i<cuerpos.size();i++){
        cuerpos.at(i)->actualizar(dt);
        scene->addItem(cuerpos.at(i));
    }
}

MainWindow::~MainWindow()
{
    // Este metodo elimina la interfaz, el timer y la escena
    delete ui;
    delete timer;
    delete scene;
}


void MainWindow::actualizar()
{
    /* Este método es el respondable de actualizar la información de los planetas, tanto en la interfaz
    *  como sus posiciones en la escena. Lo que hace es que por cada cuerpo, llama al método interno
    *  "acelerar" de la clase Cuerpo, para calcular los ángulos, el radio de distancia, y demas información,
    *  para luego llamar al método "actualizar" de Cuerpograf, que se encarga de mover el cuerpo por la escena
    *  de acuerdo a las posiciones calculadas con el método interno "actualizar" de la clase Cuerpo.
    * También, actualiza la información del cuerpo a visualizar en la interfaz.
    */

    // Se va sumando el tiempo transcurrido
    tiempo+=1;

    // Si no quedan cuerpos en movimiento, se detiene la ejecución del timer
    if (cuerpos.size()==0){
        timer->stop();
    }

    // Por cada cuerpo, realizamos los cálculos de acuerdo a la información del sol, que se encuentra en la primera
    //   posición de la lista de cuerpos
    for (int i=0; i<cuerpos.size();i++){
        for (int j=0; i<cuerpos.size();i++) {
            if (i!=j){
                cuerpos.at(i)->getEsf()->acelerar(cuerpos.at(j)->getEsf()->getX(),cuerpos.at(j)->
                    getEsf()->getY(),cuerpos.at(j)->getEsf()->get_mass());
            }
        }
    }

    // Finalmente se realiza la actualización de la posición del cuerpo
    for(int i=0;i<cuerpos.size();i++){
        cuerpos.at(i)->actualizar(dt);
    }
}

void MainWindow::on_pushButton_clicked()
{
    // Cuando se presione el botón, comienza a ejecutarse el timer
    timer->start(dt);
}


