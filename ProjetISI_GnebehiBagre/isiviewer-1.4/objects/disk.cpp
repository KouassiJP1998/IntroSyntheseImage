#include "disk.h"


void Disk::dessinSommet() {


    //x = rayon * cos (theta)
    //y = rayon * sin (theta)

    for (int i=0; i < m_inc; i++){

        addVertex((m_rayon*cos(i*(m_angle))),(m_rayon*sin(i*(m_angle))),m_z);
    }

    //origine du cercle en 0 0 0
    addVertex(m_x,m_y,m_z);
}

void Disk::dessinTriangle() {

    for(int i=0; i<m_inc; i++){

        addTriangle(m_inc,i%m_inc,(i+1)%m_inc);
    }
}


// CONSTRUCTEUR
Disk::Disk (int inc) {

    _name = "Disk";
    m_x = 0.f;
    m_y = 0.f;
    m_z = 0.f;
    m_rayon = 1.f;

    //valeur de résolution <=inc et >=20
    m_inc = inc < 20 ? 20 : inc;

    m_angle = ((2*M_PI)/m_inc);

    //sommets
    dessinSommet();
    //triangles
    dessinTriangle();


    computeNormalsT();
    computeNormalsV();
}
