/**
 * Fonctions pour les couleurs et dessin de composantes cercles et rectangles
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#if defined __linux
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_image.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif
#include "geometry/canonics.h"

static const float PI = 3.1415926535;
static int SEGMT = 64;

/**
 * Initialise une couleur RGV
 * @param r,g,b  int valeurs des composantes
 * @return CustomColor
 */
CustomColor color(int r, int g, int b){
  CustomColor c;
  c.r = r;
  c.g = g;
  c.b = b;
  return c;
}

/**
 * Affiche un cercle
 * @param full  1 : cercle plein, 0: cercle vide
 * @param color struct CustomColor (couleur au format rgb)
 */
void draw_circle(int full, CustomColor color) {
  float x,y;
  float theta;
  int mode;
  mode = (full)?GL_POLYGON:GL_LINE_LOOP;
  glBegin(mode);
  glColor3ub(color.r, color.g, color.b);
  for (theta = 0; theta<2*PI; theta+= (2*PI)/SEGMT) {
    x = 0.5*cos(theta);
    y = 0.5*sin(theta);
    glVertex2f(x, y);
  }
  glEnd();
}

/**
 * Affiche un rectangle
 * @param color   struct CustomColor (couleur au format rgb)
 * @param height float height
 * @param length float length
 */
void draw_rectangle(CustomColor color, float height, float length) {
  glBegin(GL_POLYGON);
  glColor3ub(color.r, color.g, color.b);
  glTexCoord2f(0,0);
  glVertex2f(-(length/2), height/2);
  glTexCoord2f(1,0);
  glVertex2f(length/2, height/2);
  glTexCoord2f(1,1);
  glVertex2f(length/2, -(height/2));
  glTexCoord2f(0,1);
  glVertex2f(-(length/2), -(height/2));

  glEnd();
}
