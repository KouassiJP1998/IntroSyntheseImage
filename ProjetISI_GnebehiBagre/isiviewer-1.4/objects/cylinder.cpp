#include "cylinder.h"


void Cylinder::dessinSommet(float niveau){


    //x = rayon * cos (theta)
    //y = rayon * sin (theta)

    for (int i = 0; i < m_inc; i++){
        addVertex((m_rayon*cos(i*(m_angle))), (m_rayon*sin(i*(m_angle))), niveau);
    }
}

void Cylinder::dessinBaseTriangle() {

    for(int i = 0; i<m_inc; i++){

        addTriangle(0.f,(i+1)%m_inc+1,i%m_inc+1);
    }
}

void Cylinder::dessinMileuTriangle(){

    float p1,p2,p3;

    for (int niveau = 0; niveau < m_niveau; niveau++) {

        for (int i = 0; i < m_inc; i++) {

            p1 = (i % m_inc + m_inc * niveau + 1);
            p2 = i % m_inc + m_inc * (niveau + 1) + 1;
            p3 = ((i+1) % m_inc + m_inc * niveau + 1);
            addTriangle(p1, p3, p2);

            p1 = (i % m_inc + m_inc * (niveau + 1) + 1);
            p2 = ((i + 1) % m_inc + m_inc * (niveau + 1) + 1);
            p3 = ((i + 1) % m_inc + m_inc * niveau + 1);
            addTriangle(p1, p3, p2);
        }
    }
}

void Cylinder::dessinHautTriangle() {

    //centre du cercle(251)
    int centre = (m_niveau+1)*m_inc+1;

    int rangeSommets = centre-m_inc;

    for(int i = 0; i<m_inc; i++){

        addTriangle(centre,i%m_inc+rangeSommets,(i+1)%m_inc+rangeSommets);
    }
}


Cylinder::Cylinder (int inc) {

    _name = "Cylinder";
    m_x = 0.f;
    m_y = 0.f;
    m_z = -1.f;
    m_rayon = 1.f;

    m_niveau = 4;

    //centre du cercle du "bas"
    addVertex(m_x, m_y, m_z);

    // la valeur de résolution >=20 et <=inc
    m_inc = inc < 20 ? 20 : inc;

    m_angle = ((2*M_PI)/m_inc);

    //5 niveaux par palier
    for (float niveau = -1.f; niveau <= 1.f; niveau+=0.5f) {

        //sommets par niveau
        dessinSommet(niveau);
    }

    m_z=1.f;
    //cercle du "haut" (0 0 1)
    this->addVertex(m_x,m_y,m_z);

    //cercle du bas
    this->dessinBaseTriangle();

    //partie centre
    this->dessinMileuTriangle();

    //cercle du haut
    this->dessinHautTriangle();


    computeNormalsT();
    computeNormalsV();
}
