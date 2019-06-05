#include "cone.h"

void Cone::dessinSommet() {

    //x se calcule : x = rayon * cos (theta)
    //y se calcule : y = rayon * sin (theta)

    for (float niveau = 0.5f; niveau >= -1.f; niveau -= 0.5f) {

        for (int i= 0; i < m_inc; i++){

            m_angle = 2*M_PI/m_inc;
            addVertex((m_rayon*cos(i*m_angle)),(m_rayon*sin(i*m_angle)), niveau);
        }
        m_rayon+=0.25f;
    }
}

void Cone::dessinHautTriangle() {

    for(int i = 0; i<m_inc; i++){

        // ajout des triangles (0,1,2) (0,2,3) etc... avec 0 le sommet
        addTriangle(0.f,i%m_inc+1,(i+1)%m_inc+1);
    }
}


void Cone::dessinMilieuTriangle() {

    int P1Bas, P2Bas, PHaut;
    // m_niveau-1 car je m'occupe des niveaux 1(base), 2 et 3. (le 4 etant deja fait avec la fonction traceTrianglesHaut)
    for(int niveau = 0; niveau<(m_niveau-1); niveau++){

        for (int i = 0; i<m_inc; i++) {

            P1Bas = i%m_inc+m_inc*niveau+1;
            P2Bas = i%m_inc+m_inc*(niveau+1)+1;
            PHaut = (i+1)%m_inc+m_inc*niveau+1;
            addTriangle(P1Bas, P2Bas, PHaut);

            P1Bas = i%m_inc+m_inc*(niveau+1)+1;
            P2Bas = (i+1)%m_inc+m_inc*(niveau+1)+1;
            PHaut = (i+1)%m_inc+m_inc*niveau+1;
            addTriangle(P1Bas, P2Bas, PHaut);
        }
    }

}

void Cone::dessinBaseTriangle() {

    // le centre du cercle est le dernier sommet ajouté (201)
    int centre = m_niveau*m_inc+1;
    // les sommets de la base sont les m_inc avant-derniers sommets, le dernier étant le centre du cercle de base (ici de 150 à 200)
    int rangeSommets = centre-m_inc;

    for(int i = 0; i<m_inc; i++){

        //triangles du cercle de base: ici triangle (201,150,151) (201,151,152)
        addTriangle(centre,(i+1)%m_inc+rangeSommets,i%m_inc+rangeSommets);
    }
}


Cone::Cone (int inc) {

    _name = "Cone";
    m_x = 0.f;
    m_y = 0.f;
    m_z = 1.f;
    m_rayon = 0.25f;
    // valeur de résolution
    m_inc = inc < 20 ? 20 : inc;
    //nombre de niveau dans le cone
    m_niveau = 4;
    m_angle = ((2*M_PI)/m_inc);

    //sommet du cone
    addVertex(m_x,m_y,m_z);
    //sommets du cone
    dessinSommet();
    m_z = -1.f;
    //base du cone en 0 0 -1
    addVertex(m_x,m_y,m_z);
    //cone du "haut"
    dessinHautTriangle();

    dessinMilieuTriangle();
    //cercle du bas
    dessinBaseTriangle();

    //les normales
    computeNormalsT();
    computeNormalsV();
}
