#ifndef PLAYER_H_
#define PLAYER_H_

#include "elements/barre.h"
#include "elements/ball.h"

typedef struct _player{
  int id;
  float vie;
  struct _ball * ball;
  struct _barre * barre;
}Player;

void init_player(Player *p, int id);
void free_player(Player *p);

#endif
