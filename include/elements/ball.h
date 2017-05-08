#ifndef BALL_H_
#define BALL_H_

typedef struct _ball{
  struct _point3D position;
  float diam;
  struct _customColor color;
  struct _vector3D velocity;
}Ball;

void init_ball(Ball *b);
void draw_ball(Ball b);
void update_position(Ball *b);
void check_edges(Ball *b);

#endif
