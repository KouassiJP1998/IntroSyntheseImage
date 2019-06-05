#ifndef TORUS_H
#define TORUS_H

#include "triMesh.h"
#include <math.h>

class Torus : public TriMesh {
public:

    Torus(int);
    virtual ~Torus(){};

protected:

    float corne;
    int m_inc;
};

#endif // TORUS_H
