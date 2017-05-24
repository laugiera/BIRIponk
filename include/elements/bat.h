#ifndef BAT_H_
#define BAT_H_

#include "elements/gameboard.h"

typedef struct _bat{
  struct _point3D position;
  float length;
  float height;
  struct _customColor color;
  struct _vector3D velocity;
}Bat;

void init_bat(Bat *bat, struct _player *p);
void draw_bat(Bat bat);
void update_bat_position(Bat *bat, int sens);


#endif
