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
  p->vie = 5.0;
  p->ball = malloc(sizeof(Ball));
  if(!p->ball)
    exit(1);
  p->barre = malloc(sizeof(Barre));
  if(!p->barre)
    exit(1);
  init_ball(p->ball);
  init_barre(p->barre);
}

void free_player(Player *p){
  free(p->ball);
  free(p->barre);
}
