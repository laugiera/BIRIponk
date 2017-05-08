#include "geometry/point_vect.h"
#include "math.h"

Point3D pointXY(float x, float y ){
  Point3D p = {x,y};
  return p;
}

Vector3D vectorXY(float x, float y){
  Vector3D v = {x, y};
  return v;
}

Vector3D vector(Point3D A, Point3D B){
  Vector3D v = vectorXY(B.x-A.x, B.y-A.y);
  return v;
}

Point3D pointPlusVector(Point3D P, Vector3D V){
  Point3D p = pointXY(P.x+V.x, P.y+V.y);
  return p;
}

Vector3D addVectors(Vector3D A, Vector3D B){
  Vector3D v = vectorXY(A.x+B.x, A.y+B.y);
  return v;
}

Vector3D subVectors(Vector3D A, Vector3D B){
  Vector3D v = vectorXY(A.x-B.x, A.y-B.y);
  return v;
}

Vector3D multVector(Vector3D V, float s){
  Vector3D v = vectorXY(V.x*s, V.y*s);
  return v;
}

Vector3D DivVector(Vector3D V, float s){
  Vector3D v = vectorXY(V.x/s, V.y/s);
  return v;
}

float dotProduct(Vector3D A, Vector3D B){
  float result = A.x*B.x + A.y*B.y;
  return result;
}

float norm(Vector3D V){
  float norm = sqrt((V.x*V.x)+(V.y*V.y));
  return norm;
}

Vector3D normalie(Vector3D V){
  float n = norm(V);
  Vector3D v = DivVector(V, n);
  return v;
}
