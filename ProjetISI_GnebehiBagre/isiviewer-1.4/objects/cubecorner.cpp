#include "cubecorner.h"

CubeCorner::CubeCorner() : TriMesh() {

    _name = "CubeCorner";
    static const GLfloat v[10][3] = {
        {-1,1,-1},{-1,1,1},{1,1,1},{1,1,-1},{-1,-1,-1},{-1,-1,1},{0,-1,1},{1,0,1},{1,-1,0},{1,-1,-1}
      };

      // triangles vertex indices
      static const GLint t[18][3] = {
        {1,2,0},{3,0,2},{0,5,1},{4,5,0},{4,0,9},{3,9,0},{1,5,2},{4,9,5},{3,2,9},{4,9,0},{3,0,9},{6,8,7},  // normal side
        {5,6,2},{7,2,6},{5,9,6},{8,6,9},{9,2,8},{7,8,2}};

    // Fill vertices vector
    for (int i=0; i<10 ; ++i)
        this->addVertex(v[i][0], v[i][1], v[i][2]);

    // Fill triangles vector
    for (int i=0; i<18; ++i)
        this->addTriangle(t[i][0], t[i][1] ,t[i][2]);

        computeNormalsT();
        computeNormalsV();
}
