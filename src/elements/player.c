#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#if defined __linux
#include <GL/gl.h>
#include <GL/glu.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif
#include "geometry/canonics.h"
#include "geometry/point_vect.h"
#include "fonctions.h"
#include "elements/player.h"

void init_player(Player *p, int id){
  p->id=id;
  p->life = 5.0;
  p->ball = malloc(sizeof(Ball));
  if(!p->ball)
    exit(1);
  p->bat = malloc(sizeof(Bat));
  if(!p->bat)
    exit(1);
  init_bat(p->bat, p);
  init_ball(p->ball, p);


}

void free_player(Player *p){
  free(p->ball);
  free(p->bat);
}

void draw_life(Player *p){
  int i, taille = 10;
  Point3D position = p->start_position;
  if(p->start_orientation.y == -1)
    position.x -= 100;
  CustomColor c = color(67,202,112);
  for(i=0; i<5; i++){
    position.x += 1.5 * taille;
    if(i+1 > p->life)
      c = color(100,107,102);
    glPushMatrix();
    glTranslatef(position.x, position.y, 0);
    draw_rectangle(c, taille,taille);
    glPopMatrix();
  }
}
