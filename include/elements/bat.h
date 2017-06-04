/**
 * Fonctions liées à la barre
 */

#ifndef BAT_H_
#define BAT_H_

#include "elements/gameboard.h"

typedef struct _bat{
  struct _Point2D position;
  float length;
  float height;
  struct _customColor color;
  struct _Vector2D velocity;
}Bat;

void init_bat(Bat *bat, struct _player *p);
void draw_bat(Bat bat);
void update_bat_position(Bat *bat, int sens);

#endif
