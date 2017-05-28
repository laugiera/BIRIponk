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

void init_ball(Ball *b, Player *p){
  CustomColor vert = color(100, 200, 0);
  b->player = p;
  b->position = pointPlusVector(b->player->bat->position, multVector(b->player->start_orientation, b->player->bat->height/2+b->diam/2+1));/*test +1 pour bug décolage*/
  b->diam = 20;
  b->color = vert;
  b->velocity = p->start_orientation;
  b->speed = 0;
  /*b->speed = 0.6;*/
}

void draw_ball(Ball b){
  glPushMatrix();
  glTranslatef(b.position.x, b.position.y, 0);
  glScalef(b.diam,b.diam,0);
  draw_circle(1, b.color);
  glPopMatrix();
}

void update_ball_position(Ball *b, Gameboard *gb){
  if(b->speed == 0){
    resting_ball(b);
    return;
  }
  Vector3D acceleration = multVector(normalize(b->velocity), b->speed);
  b->position = pointPlusVector(b->position, addVectors(b->velocity, acceleration));
  ball_check_death(b, gb);
  ball_check_edges(b);
  ball_check_bat(b, gb);
  ball_check_bricks(b, gb);

}

void ball_check_edges(Ball *b){
  if(b->position.x>= 100-b->diam/2 || b->position.x<= -100+b->diam/2) {
      b->velocity.x *= -1;
      if(b->velocity.x == 0) {b->velocity.x = b->velocity.y;}
    }
  if(b->position.y>= 100-b->diam/2 || b->position.y<= -100+b->diam/2)
    {
      b->velocity.y *= -1;
    }
  /*rajouter des sécurité sortie du cadre et bug le long des bords*/
}

void ball_check_bat(Ball *ball, Gameboard *board) {
  int i;
  for (i=0; i<board->nb_players; i++){
    Bat bat = *board->players[i].bat;
    float dist_x = fabs(bat.position.x-ball->position.x)-ball->diam/2;
    float dist_y = fabs(bat.position.y-ball->position.y)-ball->diam/2;
    if(dist_x <= bat.length/2 && dist_y <= bat.height/2){
      float ratio = (ball->position.x-bat.position.x)/bat.length/2;
      ball->velocity.x = ratio;
      ball->velocity.y *= -1;
      return;
    }
  }
  return;
}

void ball_check_death(Ball *ball, Gameboard *board){
 int i;
 for (i=0; i<board->nb_players; i++){
   Player *p = &(board->players[i]);
   float factor = p->start_orientation.y;
   /* à réutiliser pour faire le 2++ joueurs
   if (factor ==0){
     factor = board->players[i].start_orientation.x;
   }
   */
   float dist_y = (p->start_position.y - ball->position.y) + factor*ball->diam/2;
   factor *= -1;
   dist_y *= factor;
   if (dist_y <= 0) {
      printf("DEATH\n");
      p->life -= 1.0;
      ball->speed = 0;
      /*resting_ball(b);*/
      /* à garder si on implement le choix de quand commencer la partie
      ball->velocity = vectorXY(0,0);
       */
      ball->velocity = ball->player->start_orientation;

   }
 }
}

int ball_check_brick(Ball *ball, Brick *brick, Gameboard *board) {
    float dist_x = fabs(brick->position.x-ball->position.x)-ball->diam/2;
    float dist_y = fabs(brick->position.y-ball->position.y)-ball->diam/2;

    if((int)dist_x == (int)brick->length/2 && (int)dist_y == (int)brick->height/2){
      ball->velocity = multVector(ball->velocity, -1);
      return ball_brick_collision(ball, brick, board);
    } else if ((int)dist_x == (int)brick->length/2 && dist_y < brick->height/2) {
      ball->velocity.x *= -1;
      return ball_brick_collision(ball, brick, board);
    } else if (dist_x < brick->length/2 && (int)dist_y == (int)brick->height/2) {
      ball->velocity.y *= -1;
      return ball_brick_collision(ball, brick, board);
    }
  return 0;
}

void ball_check_bricks(Ball *ball, Gameboard *board){
  int i;
  /*changer pour optimiser en fct du nb de bricks*/
  for(i=0; i<board->nb_bricks; i++){
    if(board->bricks[i].status == ON){
      if(ball_check_brick(ball, &(board->bricks[i]), board)){
        printf("check brick\n");
      }
    }
  }
}

int ball_brick_collision(Ball *ball, Brick *brick, Gameboard *board){
  brick->status = OFF;
  /*gestion des bonus*/
  return 1;
}

void resting_ball(Ball *ball){
  ball->position = pointPlusVector(ball->player->bat->position, multVector(ball->player->start_orientation, ball->player->bat->height/2+ball->diam/2+1));
}
