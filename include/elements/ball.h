#ifndef BALL_H_
#define BALL_H_

#include "elements/gameboard.h"

typedef struct _ball{
  struct _point3D position;
  float diam;
  struct _customColor color;
  struct _vector3D velocity;
}Ball;

void init_ball(Ball *b);
void draw_ball(Ball b);
void update_ball_position(Ball *b, Gameboard *board);
void ball_check_edges(Ball *b);
void ball_check_bat(Ball *ball, Gameboard *board);

#endif
