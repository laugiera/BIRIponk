/**
 * Fonctions liées au joueur
 */

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#if defined __linux
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_image.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif
#include "geometry/canonics.h"
#include "geometry/point_vect.h"
#include "fonctions.h"
#include "elements/player.h"


/**
 * Initialise une structure Joueur passée en paramètre avec un id
 * les champs start_orientation et start_position doivent avoir été initialisé au préallable
 * en fonction du nombre de joueurs.
 * @param p  pointeur sur une structure Player
 * @param id int de 0 au nombre de joueur-1
* @param c CustomColor couleur attribuée au joueur
 */
void init_player(Player *p, int id, CustomColor c){
  p->id=id;
  p->life = 5.0;
  p->ball = malloc(sizeof(Ball));
  if(!p->ball)
    exit(1);
  p->bat = malloc(sizeof(Bat));
  if(!p->bat)
    exit(1);
  p->color = c;
  init_bat(p->bat, p);
  init_ball(p->ball, p);


}

/**
 * Libère l'espace mémoire attribué à un joueur
 * @param p pointeur sur une structure Player
 */
void free_player(Player *p){
  free(p->ball);
  free(p->bat);
}

/**
 * Affiche la barre de vie d'un joueur
 * @param p pointeur sur une structure Player
 */
void draw_life(Player *p){
  int i, taille = 10;
  Point2D position = p->start_position;
  if(p->start_orientation.y == -1)
    position.x -= 100;
  CustomColor c = color(p->color.r+50, p->color.g+10,p->color.b+10);
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
