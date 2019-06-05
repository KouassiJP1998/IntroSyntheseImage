#include "diskhole.h"

void DiskHole::dessinSommet(){


    //x = rayon * cos (theta)
    //y = rayon * sin (theta)

    for (int i = 0; i < m_inc; i++){

        addVertex((m_rayon*cos(i*(m_angle))),(m_rayon*sin(i*(m_angle))),m_z);
    }
}

void DiskHole::dessinTriangle() {

    float p1,p2,p3;

    for (int i = 0; i < 1; i++) {

        for (int j = 0; j < m_inc; j++) {

            p1 = (j % m_inc + m_inc * i + 1);
            p2 = j % m_inc + m_inc * (i + 1) + 1;
            p3 = ((j + 1) % m_inc + m_inc * i + 1);
            addTriangle(p1, p2, p3);

            p1 = (j % m_inc + m_inc * (i + 1) + 1);
            p2 = ((j + 1) % m_inc + m_inc * (i + 1) + 1);
            p3 = ((j + 1) % m_inc + m_inc * i + 1);
            addTriangle(p1, p2, p3);
        }
    }
}


DiskHole::DiskHole (float rayon, int inc) {

    _name = "DiskHole";
    m_x = 0.f;
    m_y = 0.f;
    m_z = 0.f;

    //origine des cercles (0,0,0)
    addVertex(m_x,m_y,m_z);

    //valeur de résolution
    m_inc = inc < 20 ? 20 : inc;

    // calcul de l'angle
    m_angle = ((2*M_PI)/m_inc);
    // vérification validation du rayon
    if (rayon > 1.f) {
        m_rayon = 1.f;
    } else if (rayon <= 0.f) { // si valeur rayon invalide, minimum est 0.2
        m_rayon = 0.2f;
    } else {
        m_rayon = rayon;
    }

    //rayon du plus petit cercle = 1/2 du plus grand.
    m_rayon/=2.f;
    //sommets du petit cercle
    dessinSommet();

    //rayon d'origine
    m_rayon*=2;
    //ajout des sommets
    dessinSommet();

    //sommets du petit et grand disque
    this->dessinTriangle();


    computeNormalsT();
    computeNormalsV();
}
