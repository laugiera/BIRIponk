#ifndef BAT_H_
#define BAT_H_

typedef struct _bat{
  struct _point3D position;
  float length;
  float height;
  struct _customColor color;
  struct _vector3D velocity;
}Bat;

void init_bat(Bat *br);
void draw_bat(Bat br);
void update_bat_position(Bat *br, int sens);


#endif
