#ifndef BRICK_H_
#define BRICK_H_

typedef enum { ON, OFF } state;

typedef enum { ball_speed_slow, ball_speed_fast, life_bonus, life_malus } bonus;

typedef struct _brick{
  struct _point3D position;
  float length;
  float height;
  bonus alteration;
  state status;
}Brick;


#endif
