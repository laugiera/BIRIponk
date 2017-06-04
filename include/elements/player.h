/**
 * Fonctions liées au joueur
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "elements/bat.h"
#include "elements/ball.h"

typedef struct _player{
  int id;
  struct _Point2D start_position;
  struct _Vector2D start_orientation;
  float life;
  struct _ball * ball;
  struct _bat * bat;
  CustomColor color;
}Player;

void init_player(Player *p, int id, CustomColor c);
void free_player(Player *p);
void draw_life(Player *p);

#endif
