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
#include "elements/barre.h"

void init_barre(Barre *br){
  CustomColor rouge = {255, 50, 0};
  br->hauteur = 10;
  br->largeur = 30;
  br->position = pointXY(0,-(100-(br->hauteur/2)));
  br->color = rouge;
  br->velocity = vectorXY(1,1);
}

void draw_barre(Barre br){
  glPushMatrix();
  glTranslatef(br.position.x, br.position.y, 0);
  draw_rectangle(br.color, br.hauteur, br.largeur);
  glPopMatrix();
}

void update_br_position(Barre *br, int sens){
  switch (sens) {
    case droite:
      if(br->position.x < 100-(br->largeur/2))
        br->position.x +=1*br->velocity.x;
      break;
    case gauche:
      if(br->position.x > -100+(br->largeur/2))
        br->position.x -=1*br->velocity.x;
      break;
  }
}
