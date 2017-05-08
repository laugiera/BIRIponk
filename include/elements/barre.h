#ifndef BARRE_H_
#define BARRE_H_

typedef struct _barre{
  struct _point3D position;
  float largeur;
  float hauteur;
  struct _customColor color;
  struct _vector3D velocity;
}Barre;

void draw_barre(Barre br);
void update_br_position(Barre *br, int sens);


#endif
