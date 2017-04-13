#ifndef POINT_VECT_H
#define POINT_VECT_H


typedef struct _vector3D{
  float x, y, z;
}Vector3D;

typedef struct _point3D{
  float x, y, z;
}Point3D;

Point3D pointXYZ(float x, float y, float z);
Vector3D vectorXYZ(float x, float y, float z);
Vector3D vector(Point3D A, Point3D B);
Point3D pointPlusVector(Point3D P, Vector3D V);
Vector3D addVectors(Vector3D A, Vector3D B);
Vector3D subVectors(Vector3D A, Vector3D B);
Vector3D multVector(Vector3D V, float s);
Vector3D DivVector(Vector3D V, float s);
float dotProduct(Vector3D A, Vector3D B);
float norm(Vector3D V);
Vector3D normalize(Vector3D V);

#endif
