#include "sphere.h"


void Sphere::dessinSommet() {


    //x = rayon * cos (theta) * sin (phi)
    //y = rayon * sin (theta) sin (phi)
    //z = rayon * cos (phi)

    float x, y, z;

    for(int niveau=1; niveau<m_inc; niveau++){

        m_angle_phi = PI/m_inc;

        for(int i=0; i < m_inc; i++){

            x = m_rayon*cos(i*m_angle_theta)*sin(niveau*m_angle_phi);
            y = m_rayon*sin(i*m_angle_theta)*sin(niveau*m_angle_phi);
            z = m_rayon*cos (niveau*m_angle_phi);

            addVertex(x,y,z);
        }
    }
}

void Sphere::dessinHautTriangle() {

    for(int i = 0; i<m_inc; i++){

        /* on trace les triangles (0,1,2) (0,2,3) etc... avec 0 le sommet "pole nord" de la sphere */
        addTriangle(0.f,i%m_inc+1,(i+1)%m_inc+1);
    }
}


void Sphere::dessinMilieuTriangle(){

    float p1,p2,p3;

    for (int niveau = 0; niveau < m_inc-2; niveau++) {

        for (int i = 0; i < m_inc; i++) {

            p1 = (i % m_inc + m_inc * niveau + 1);
            p2 = i % m_inc + m_inc * (niveau + 1) + 1;
            p3 = ((i+1) % m_inc + m_inc * niveau + 1);
            addTriangle(p1, p2, p3);

            p1 = (i % m_inc + m_inc * (niveau + 1) + 1);
            p2 = ((i + 1) % m_inc + m_inc * (niveau + 1) + 1);
            p3 = ((i + 1) % m_inc + m_inc * niveau + 1);
            addTriangle(p1, p2, p3);
        }
    }
}

void Sphere::dessinBasTriangle() {

    int centre = m_inc*(m_inc-1)+1;
    int rangeSommets = centre -m_inc;

    for(int i = 0; i<m_inc; i++){

        //les triangles (0,1,2) (0,2,3) avec 0 le plus haut sommet
        addTriangle(centre,(i+1)%m_inc+rangeSommets,i%m_inc+rangeSommets);
    }
}


Sphere::Sphere (int inc) {

    _name = "Sphere";
    m_x = 0.f;
    m_y = 0.f;
    m_z = 1.f;
    m_rayon = 1.f;


    m_inc = inc < 20 ? 20 : inc;

    //angles theta et phi qui varient respecivement entre -2pi/2pi et -pi/pi
    m_angle_theta = ((2*M_PI)/m_inc);
    m_angle_phi = M_PI/m_inc;


    //premier sommet qui sera le plus haut sommet
    addVertex(m_x,m_y,m_z);

    //tous les sommets
    dessinSommet();

    //dernier sommet(le plus bas)
    m_z = -1.f;
    addVertex(m_x,m_y,m_z);

    dessinHautTriangle();
    dessinMilieuTriangle();
    dessinBasTriangle();

    computeNormalsT();
    computeNormalsV();

}
