/**
 * Fonctions géométriques pour les vecteurs et les points
 */

#include "geometry/point_vect.h"
#include "math.h"

/**
 * Initialise un point 2D
 * @param x,y  int valeurs des composantes
 * @return Point2D
 */
Point2D pointXY(float x, float y ){
  Point2D p = {x,y};
  return p;
}

/**
 * Initialise un vecteur 2D
 * @param x,y  int valeurs des composantes
 * @return Vector2D
 */
Vector2D vectorXY(float x, float y){
  Vector2D v = {x, y};
  return v;
}

/**
 * Initialise un vecteur 2D
 * @param A,B Point2D
 * @return Vector2D
 */
Vector2D vector(Point2D A, Point2D B){
  Vector2D v = vectorXY(B.x-A.x, B.y-A.y);
  return v;
}

/**
 * Translation de point par un vecteur
 * @param P Point2D point de base
 * @param V Vector2D  vecteur
 * @return Point2D  point translaté
 */
Point2D pointPlusVector(Point2D P, Vector2D V){
  Point2D p = pointXY(P.x+V.x, P.y+V.y);
  return p;
}

/**
 * Ajouts de vecteurs
 * @param A,B Vector2D  vecteurs
 * @return Vector2D
 */
Vector2D addVectors(Vector2D A, Vector2D B){
  Vector2D v = vectorXY(A.x+B.x, A.y+B.y);
  return v;
}

/**
 * Soustraction de vecteurs
 * @param A,B Vector2D  vecteurs
 * @return Vector2D
 */
Vector2D subVectors(Vector2D A, Vector2D B){
  Vector2D v = vectorXY(A.x-B.x, A.y-B.y);
  return v;
}

/**
 * Multiplication de vecteurs
 * @param V Vector2D vecteur
 * @param s float multiplicateur
 * @return Vector2D
 */
Vector2D multVector(Vector2D V, float s){

  Vector2D v = vectorXY(V.x*s, V.y*s);
  return v;
}

/**
 * Division de vecteurs
 * @param V Vector2D vecteur
 * @param s float diviseur
 * @return Vector2D
 */
Vector2D DivVector(Vector2D V, float s){
  if(s == 0) {
    return vectorXY(0,0);
  }
  Vector2D v = vectorXY(V.x/s, V.y/s);
  return v;
}

/**
 * Produit scalaire
 * @param A,B Vector2D  vecteurs
 * @return float produit scalaire de A et B
 */
float dotProduct(Vector2D A, Vector2D B){
  float result = A.x*B.x + A.y*B.y;
  return result;
}

/**
 * Module
 * @param V Vector2D vecteur
 * @return float module de V
 */
float norm(Vector2D V){
  float norm = sqrt((V.x*V.x)+(V.y*V.y));
  return norm;
}

/**
 * Normalise un vecteur
 * @param V Vector2D vecteur
 * @return Vector2D
 */
Vector2D normalize(Vector2D V){
  float n = norm(V);
  if(n == 0) {
    return vectorXY(0,0);
  }
  Vector2D v = DivVector(V, n);
  return v;
}
