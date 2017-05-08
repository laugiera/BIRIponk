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
#include "geometry/point_vect.h"
#include "fonctions.h"
#include "elements/ball.h"

void init_ball(Ball *b){
  CustomColor vert = {100, 200, 0};
  b->position = pointXY(0,0);
  b->diam = 40;
  b->color = vert;
  b->velocity = vectorXY(1,1);
}

void draw_ball(Ball b){
  glPushMatrix();
  glTranslatef(b.position.x, b.position.y, 0);
  glScalef(b.diam,b.diam,0);
  draw_circle(1, b.color);
  glPopMatrix();
}

void update_position(Ball *b){
  b->position = pointPlusVector(b->position, b->velocity);
  check_edges(b);
}

void check_edges(Ball *b){
  if(b->position.x>= 100-b->diam/2 ||
    b->position.x<= -100+b->diam/2 ||
    b->position.y>= 100-b->diam/2)
    {
      b->velocity = multVector(b->velocity, -1);
    }
  if(b->position.y<= -100+b->diam/2){b->position.y = -100+b->diam/2;}
}
