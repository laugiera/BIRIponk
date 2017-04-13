#include "geometry/point_vect.h"
#include "math.h"

Point3D pointXYZ(float x, float y, float z){
  Point3D p = {x,y,z};
  return p;
}

Vector3D vectorXYZ(float x, float y, float z){
  Vector3D v = {x, y, z};
  return v;
}

Vector3D vector(Point3D A, Point3D B){
  Vector3D v = vectorXYZ(B.x-A.x, B.y-A.y, B.z-A.z);
  return v;
}

Point3D pointPlusVector(Point3D P, Vector3D V){
  Point3D p = pointXYZ(P.x+V.x, P.y+V.y, P.z+V.z);
  return p;
}

Vector3D addVectors(Vector3D A, Vector3D B){
  Vector3D v = vectorXYZ(A.x+B.x, A.y+B.y, A.z+B.z);
  return v;
}

Vector3D subVectors(Vector3D A, Vector3D B){
  Vector3D v = vectorXYZ(A.x-B.x, A.y-B.y, A.z-B.z);
  return v;
}

Vector3D multVector(Vector3D V, float s){
  Vector3D v = vectorXYZ(V.x*s, V.y*s, V.z*s);
  return v;
}

Vector3D DivVector(Vector3D V, float s){
  Vector3D v = vectorXYZ(V.x/s, V.y/s, V.z/s);
  return v;
}

float dotProduct(Vector3D A, Vector3D B){
  float result = A.x*B.x + A.y*B.y + A.z*B.z;
  return result;
}

float norm(Vector3D V){
  float norm = sqrt((V.x*V.x)+(V.y*V.y));
  return norm;
}

Vector3D normalize(Vector3D V){
  float n = norm(V);
  Vector3D v = DivVector(V, n);
  return v;
}
