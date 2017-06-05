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

void update_bat_position_AI(Bat *bat, Gameboard *board){
  Ball ball = choose_target_AI(bat, board);
  bat->velocity = normalize(vector(bat->position, ball.position));
  bat->position.x += bat->velocity.x;
  if(bat->position.x >= 100-(bat->length/2)) {
    bat->position.x = 100-(bat->length/2);
  } else if (bat->position.x <= -100+(bat->length/2)) {
    bat->position.x = -100+(bat->length/2);
  }
}

Ball choose_target_AI(Bat *bat, Gameboard *board) {
  float dist = 200;
  int i;
  Ball *ball;
  for (i = 0; i<board->nb_players; i++) {
    float dist_temp = norm(vector(bat->position, board->players[i].ball->position));
    if (dist_temp <= dist) {
      dist = dist_temp;
      ball = board->players[i].ball;
    }
  }
  return *ball;
}
