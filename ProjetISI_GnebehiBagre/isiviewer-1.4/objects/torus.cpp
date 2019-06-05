#include "torus.h"

Torus::Torus (int inc) {

    _name = "Torus";

    //nombre de points >=60
    m_inc = inc < 60 ? 60 : inc;

    float corne= 2*M_PI/m_inc;

    //création des vertexs
    for(float i=0; i<2*M_PI; i+=corne) {
        for(float j=0; j<2*M_PI; j+=corne) {

            float pointZ = (M_PI/2)*sin(j);
            this->addVertex((M_PI+(M_PI/2)*cos(j))*cos(i)/5, (M_PI+(M_PI/2)*cos(j))*sin(i)/5, pointZ/5);

        }

    }

    //création des triangles
    for(int ii=0; ii<m_inc; ii++) {

        for(int jj=0; jj<m_inc; jj++){

            this->addTriangle(ii+jj*(m_inc+1),(ii+1)+(jj+1)*(m_inc+1), (ii+1)+jj*(m_inc+1));
            this->addTriangle(ii+jj*(m_inc+1), ii+(jj+1)*(m_inc+1),(ii+1)+(jj+1)*(m_inc+1));
        }

    }

    computeNormalsT();
    computeNormalsV();
}
