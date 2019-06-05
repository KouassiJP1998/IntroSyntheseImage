#ifndef SPHERE_H
#define SPHERE_H

#include "triMesh.h"
#include <math.h>


class Sphere : public TriMesh {

public:

    void dessinSommet ();
    void dessinHautTriangle();
    void dessinMilieuTriangle();
    void dessinBasTriangle();

    Sphere();
    Sphere (int inc);
    virtual ~Sphere(){};

protected:

    float m_x;
    float m_y;
    float m_z;
    float m_rayon;
    int m_inc;
    float m_angle_theta;
    float m_angle_phi;
    float m_niveau;

};

#endif // SPHERE_H
