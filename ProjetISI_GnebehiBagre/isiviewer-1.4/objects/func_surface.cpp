#include <math.h>
#include <time.h>
#include "func_surface.h"


//equation fournie
float func_expo_cosinus(float x, float y) {

   return exp(-(x*x/2+y*y/2))*cos(2*x*x+2*y*y);
}

//nouvelle fonction de création d'un toboggan
float toboggan_func (float x, float y){

    return exp(x+1.5)/50+tan(y)/50;
}

float func_rand(float min, float max) {

    return (rand()/(float)RAND_MAX * max*2 + min);
}

Func_surface::Func_surface(int nbx, int nby, float minx, float maxx, float miny, float maxy, float (*pointeur)(float, float)) {

    _name ="Func_surface";

    m_nbx = nbx;
    m_nby = nby;
    m_minx = minx;
    m_maxx = maxx;
    m_miny = miny;
    m_maxy = maxy;

    float unCarre = 2*M_PI/50; //élément de quadrillage


    for(float i=m_minx; i<m_maxx; i+=unCarre) { //parcourt du quadrillage pour créer la création des sommets.

        for(float j=m_miny; j<m_maxy; j+=unCarre) {

            float pointZ = pointeur(i, j);
            this->addVertex(i/m_maxx,j/m_maxy,pointZ);
        }
    }
    for (int m = 0; m<49; m++) { //Parcours des points sur l'axe x.

        for (int n = 0; n<49; n++) { //Parcours des points sur l'axe y.

            this->addTriangle(m+n*m_nbx, (m+1)+(n+1)*m_nbx, (m+1)+n*m_nbx);
            this->addTriangle(m+n*m_nbx, m+(n+1)*m_nbx, (m+1)+(n+1)*m_nbx);
        }
    }

    computeNormalsT();
    computeNormalsV();
}

