#include "triMesh.h"

#include <glm/gtc/type_ptr.hpp>

TriMesh::TriMesh()
  : Object3D()
{
  _name="TriMesh";
}

void TriMesh::addVertex(Vertex v){
  extendBoundingBox(v);
  _vertices.push_back(v);
}
void TriMesh::addVertex(double x, double y, double z){
  addVertex(Vertex(x,y,z));
}
void TriMesh::addTriangle(Triangle t){
  _triangles.push_back(t);
}
void TriMesh::addTriangle(int v1, int v2, int v3){
  Triangle t;
  t.push_back(v1);
  t.push_back(v2);
  t.push_back(v3);
  addTriangle(t);
}
void TriMesh::addNormalT(Normal n){
  _normalsT.push_back(n);
}
void TriMesh::addNormalV(Normal n){
  _normalsV.push_back(n);
}


Vertex TriMesh::getVertex(int i){
  return _vertices[i];
}


void TriMesh::computeBoundingBox(){
  if(_vertices.size()<1) return;

  _bBoxMax=_vertices[0];
  _bBoxMin=_vertices[0];
  for(unsigned int i=0; i<_vertices.size(); ++i)
    extendBoundingBox(_vertices[i]);
}

void TriMesh::computeNormalsT(){
  _normalsT.empty();

  // v1, v2, v3 sont les 3 sommets du triangle ABC
  // u et v sont les vecteurs AB et AC
  Vertex v1, v2, v3, u, v;
  Normal n;



  // nous parcourous l'ensemble des triangles et calculons pour chaque triangle sa normale

  for (int i=0; i<_triangles.size(); i++) {



          v1 = _vertices[_triangles[i][0]]; // A
          v2 = _vertices[_triangles[i][1]]; // B
          v3 = _vertices[_triangles[i][2]]; // C

          u = v2-v3; // AB = coord(B)-coord(A)
          v = v2-v1; // AC = coord(C)-coord(A)



      // la normale de u et v est le produit vectorielle de u et v
      // comme indiqué sur le sujet du TP, nous utilisons la fonction cross de glm
      n=glm::normalize(glm::cross(u,v)); // on normalise
      this->addNormalT(n);
  }
}


void TriMesh::computeNormalsV(float angle_threshold){
  _normalsV.empty();

  // Compute a normal for each vertex of each triangle
  // and put it in normalsV vector.
  // Each normal is the average of adjacent triangle normals.
  // Only normals whose angle with the current triangle normal
  // is below the angle_threshold is taken into account.



  Normal n(0,0,0);
     int nbDiv=0;//Le dividende qui permet de stocker le nombre de triangles adjacents à un certain triangle.
     int s; //Une vertex d'un triangle.
     for(unsigned int i=0; i<_triangles.size(); i++){//parcours tous les triangles
         for(unsigned int v=0; v<3; v++) {//parcours les sommets de chaque triangles
             nbDiv=0;// Réinitialisation du nombre de triangles voisins.
             n[0]=1;
             n[1]=1;
             n[2]=1;
             s = _triangles[i][v];
             for(unsigned int t=0; t<_triangles.size(); t++){ //cherche les triangles voisins à ce sommet
                 if  (s==_triangles[t][0] || s==_triangles[t][1] || s==_triangles[t][2]) {
                         if (glm::dot(_normalsT[t], _normalsT[i]) > cos((angle_threshold*M_PI)/180)  ) { //Si le produit scalaire de deux angles est inférieur au radiant de 70 degrés
                         n[0] = n[0] + _normalsT[t][0];                                             //alors on additionne les points de la normale du triangle adjacent avec
                         n[1] = n[1] + _normalsT[t][1];                                             //les points d'une normale initialisée à (1,1,1).
                         n[2] = n[2] + _normalsT[t][2];
                         nbDiv++; //Nombre de triangles adjacents par rapport au triangle qu'on a sélectionné dans la première boucle for.
                     }
                 }
             }
             n[0] = n[0]/nbDiv;//On fait la moyenne des normales des triangles voisins.
             n[1] = n[1]/nbDiv;
             n[2] = n[2]/nbDiv;
             glm::normalize(n);
             addNormalV(n);
         }
     }
}

double TriMesh::normalize(){
  glm::vec3 size=_bBoxMax-_bBoxMin;
  glm::vec3 c=getBoundingBoxCenter();
  double scale=2/max(size.x, max(size.y,size.z));

  for(unsigned int i=0; i<_vertices.size(); ++i){
      _vertices[i]+=c;
      _vertices[i]*=scale;
    }

  _bBoxMin+=c;
  _bBoxMin*=scale;
  _bBoxMax+=c;
  _bBoxMax*=scale;

  return scale;
}


std::string TriMesh::toString(){
  ostringstream oss;
  oss<< "["<< _name <<" v:"<< _vertices.size() <<", t:"<< _triangles.size() <<"]";
  return oss.str();
}

void TriMesh::toOStream(std::ostream& out) const{
  Object3D::toOStream(out);
  out << "   v: " << _vertices.size()  << std::endl;
  out << "   t: " << _triangles.size() << std::endl;
}



void TriMesh::draw(bool flipnormals){
  unsigned int i,t;
  bool smooth;
  Normal n;

  GLint mode[1];
  glGetIntegerv(GL_SHADE_MODEL, mode);
  smooth= mode[0]==GL_SMOOTH && _normalsV.size()==_triangles.size()*3;

  if(smooth){
      glBegin(GL_TRIANGLES);
      for(t=0; t<_triangles.size(); ++t)
        for(i=0; i<3; i++){
            n=_normalsV[3*t+i];
            if(flipnormals) n*=-1;
            //        glNormal3fv(&n[0]);
            glNormal3fv(glm::value_ptr(n));
            glVertex3fv(glm::value_ptr(_vertices[_triangles[t][i]]));
          }
      glEnd();
    }else{
      glBegin(GL_TRIANGLES);
      for(t=0; t<_triangles.size(); ++t){
          n=_normalsT[t];
          if(flipnormals) n*=-1;
          glNormal3fv(glm::value_ptr(n));
          for(i=0; i<3; i++)
            glVertex3fv(glm::value_ptr(_vertices[_triangles[t][i]]));
        }
      glEnd();
    }

}


void TriMesh::drawNormals(bool flipnormals){
  unsigned int i,t;
  bool smooth;
  glm::vec3 p,n;

  GLint mode[1];
  glGetIntegerv(GL_SHADE_MODEL, mode);
  smooth= mode[0]==GL_SMOOTH && _normalsV.size()==_triangles.size()*3;

  glColor3f(1,1,1);
  if(smooth){
      for(i=0; i<_normalsV.size(); ++i){
          n=_normalsV[i];
          if(flipnormals) n*=-1;
          glNormal3fv(glm::value_ptr(n));
          n/=10;
          glBegin(GL_LINES);
          glVertex3fv(glm::value_ptr(_vertices[_triangles[i/3][i%3]]));
          glVertex3fv(glm::value_ptr(_vertices[_triangles[i/3][i%3]]+n));
          glEnd();
        }
    }else{
      for(t=0; t<_triangles.size(); ++t){
          p=  _vertices[_triangles[t][0]]
              +_vertices[_triangles[t][1]]
              +_vertices[_triangles[t][2]];
          p/=3;
          n=_normalsT[t];
          if(flipnormals) n*=-1;
          glNormal3fv(glm::value_ptr(n));
          n/=10;
          glBegin(GL_LINES);
          glVertex3fv(glm::value_ptr(p));
          glVertex3fv(glm::value_ptr(p+n));
          glEnd();
        }
    }
}

void TriMesh::drawVertices(){
  glPointSize(3.);
  glBegin(GL_POINTS);
  for(unsigned int i=0; i<_vertices.size(); ++i )
    glVertex3fv(glm::value_ptr(_vertices[i]));
  glEnd();
}
