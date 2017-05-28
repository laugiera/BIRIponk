#ifndef PLAYER_H_
#define PLAYER_H_

#include "elements/bat.h"
#include "elements/ball.h"

typedef struct _player{
  int id;
  struct _point3D start_position;
  struct _vector3D start_orientation;
  float life;
  struct _ball * ball;
  struct _bat * bat;
}Player;

void init_player(Player *p, int id);
void free_player(Player *p);


#endif
