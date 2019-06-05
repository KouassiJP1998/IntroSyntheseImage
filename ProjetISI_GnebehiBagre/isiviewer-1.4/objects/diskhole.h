#ifndef DISKHOLE_H
#define DISKHOLE_H

#include <math.h>
#include "triMesh.h"


class DiskHole : public TriMesh {

public:
    void dessinSommet();
    void dessinTriangle();

    // constructeur/destructeur
    DiskHole();
    DiskHole (float rayon, int inc);
    virtual ~DiskHole(){};

protected:
    float m_x;
    float m_y;
    float m_z;
    float m_rayon;
    int m_inc;
    float m_angle;
};

#endif // DISKHOLE_H
