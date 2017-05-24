#ifndef BALL_H_
#define BALL_H_

#include "elements/gameboard.h"

typedef struct _ball{
  struct _player *player;
  struct _point3D position;
  float diam;
  struct _customColor color;
  struct _vector3D velocity;
  float speed;
}Ball;

void init_ball(Ball *b, struct _player *p);
void draw_ball(Ball b);
void update_ball_position(Ball *b, struct _gameboard *board);
void ball_check_edges(Ball *b);
void ball_check_bat(Ball *ball, struct _gameboard *board);
void ball_check_death(Ball *ball, struct _gameboard *board);

#endif
