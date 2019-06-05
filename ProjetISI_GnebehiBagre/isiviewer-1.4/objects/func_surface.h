#ifndef FUNC_SURFACE_H
#define FUNC_SURFACE_H

#include <math.h>
#include "triMesh.h"

// j'ai mis les fonctions en dehors de la classe pour une question de portée (pour pouvoir l'utiliser dans le main avec le pointeur)

float func_expo_cosinus (float x, float y);
float toboggan_func (float x, float y);



class Func_surface : public TriMesh {

public:

    Func_surface(int nbx, int nby, float minx, float maxx, float miny, float maxy, float (*pointeur)(float, float));
    virtual ~Func_surface(){};

    float func_rand (float min, float max);

protected:
    int m_nbx;
    int m_nby;
    float m_minx;
    float m_maxx;
    float m_miny;
    float m_maxy;
};

#endif // FUNC_SURFACE_H
