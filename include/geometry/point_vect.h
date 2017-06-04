/**
 * Fonctions géométriques pour les vecteurs et les points
 */

#ifndef POINT_VECT_H
#define POINT_VECT_H

typedef struct _Vector2D{
  float x, y;
}Vector2D;

typedef struct _Point2D{
  float x, y;
}Point2D;

Point2D pointXY(float x, float y);
Vector2D vectorXY(float x, float y);
Vector2D vector(Point2D A, Point2D B);
Point2D pointPlusVector(Point2D P, Vector2D V);
Vector2D addVectors(Vector2D A, Vector2D B);
Vector2D subVectors(Vector2D A, Vector2D B);
Vector2D multVector(Vector2D V, float s);
Vector2D DivVector(Vector2D V, float s);
float dotProduct(Vector2D A, Vector2D B);
float norm(Vector2D V);
Vector2D normalize(Vector2D V);

#endif
