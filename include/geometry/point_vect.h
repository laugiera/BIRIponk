#ifndef POINT_VECT_H
#define POINT_VECT_H


typedef struct _vector3D{
  float x, y;
}Vector3D;

typedef struct _point3D{
  float x, y;
}Point3D;

Point3D pointXY(float x, float y);
Vector3D vectorXY(float x, float y);
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
