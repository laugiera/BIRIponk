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
#include "elements/bat.h"

void init_bat(Bat *bat, Player *p){
  CustomColor rouge = color(255, 50, 0);
  bat->height = 10;
  bat->length = 30;
  bat->position = pointPlusVector(p->start_position, multVector(p->start_orientation, bat->height/2));
  bat->color = rouge;
  bat->velocity = vectorXY(1,1);
}

void draw_bat(Bat bat){
  glPushMatrix();
  glTranslatef(bat.position.x, bat.position.y, 0);
  draw_rectangle(bat.color, bat.height, bat.length);
  glPopMatrix();
}

void update_bat_position(Bat *bat, int sens){
  switch (sens) {
    case droite:
      if(bat->position.x < 100-(bat->length/2))
        bat->position.x +=1*bat->velocity.x;
      break;
    case gauche:
      if(bat->position.x > -100+(bat->length/2))
        bat->position.x -=1*bat->velocity.x;
      break;
  }
}
