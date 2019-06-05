#ifndef DISK_H
#define DISK_H

#include <math.h>
#include "triMesh.h"


class Disk : public TriMesh {

public:

    void dessinSommet();
    void dessinTriangle();

    // constructeur/destructeur
    Disk();
    Disk (int inc);
    virtual ~Disk(){};

protected:
    float m_x;
    float m_y;
    float m_z;
    float m_rayon;
    int m_inc;
    float m_angle;
};

#endif // DISK_H
