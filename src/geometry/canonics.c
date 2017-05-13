#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#if defined __linux
#include <GL/gl.h>
#include <GL/glu.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif
#include "geometry/canonics.h"

static const float PI = 3.1415926535;
static int SEGMT = 64;

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
    /*glTexCoord2f(x+0.5,y+0.5);*/
    glVertex2f(x, y);
  }
  glEnd();
}

/*void draw_square(int full, CustomColor color) {
  int mode;
  if(full) {
    mode = GL_QUADS;
  } else {
    mode = GL_LINE_LOOP;
  }
  glBegin(mode);
  glColor3ub(color.r, color.g, color.b);
  glVertex2f(-0.5, -0.5);
  glVertex2f(0.5, -0.5);
  glVertex2f(0.5, 0.5);
  glVertex2f(-0.5, 0.5);
  glEnd();
}

void draw_rounded_square(int full, float radius, CustomColor color) {
  float x,y,X,Y;
  float theta;
  int mode;
  mode = (full)?GL_POLYGON:GL_LINE_LOOP;
  glBegin(mode);
  glColor3ub(color.r, color.g, color.b);

  X = (-0.5)+radius;
  Y = (-0.5)+radius;
  for (theta = -PI; theta<-PI/2; theta+= (2*PI)/SEGMT/4) {
    x = radius*cos(theta);
    y = radius*sin(theta);
    glVertex2f(X+x, Y+y);
  }
  X = (0.5)-radius;
  Y = (-0.5)+radius;
  for (theta = -PI/2; theta<0; theta+= (2*PI)/SEGMT/4) {
    x = radius*cos(theta);
    y = radius*sin(theta);
    glVertex2f(X+x, Y+y);
  }
  X = (0.5)-radius;
  Y = (0.5)-radius;
  for (theta = 0; theta<PI/2; theta+= (2*PI)/SEGMT/4) {
    x = radius*cos(theta);
    y = radius*sin(theta);
    glVertex2f(X+x, Y+y);
  }
  X = (-0.5)+radius;
  Y = (0.5)-radius;
  for (theta = PI/2; theta<PI; theta+= (2*PI)/SEGMT/4) {
    x = radius*cos(theta);
    y = radius*sin(theta);
    glVertex2f(X+x, Y+y);
  }

  glEnd();
}*/

void draw_rectangle(CustomColor color, float hauteur, float largeur) {
  glBegin(GL_POLYGON);
  glColor3ub(color.r, color.g, color.b);
  /*glTexCoord2f(0,0);*/
  glVertex2f(-(largeur/2), hauteur/2);
  /*glTexCoord2f(1,0);*/
  glVertex2f(largeur/2, hauteur/2);
  /*glTexCoord2f(1,1);*/
  glVertex2f(largeur/2, -(hauteur/2));
  /*glTexCoord2f(0,1);*/
  glVertex2f(-(largeur/2), -(hauteur/2));
  glEnd();
}
