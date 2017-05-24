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
<<<<<<< HEAD:src/elements/brique.c
#include "elements/brique.h"

void init_brique(Brique *b){
  /*charge le fichier de briques*/

}
/*pour 2 joueurs,
    nb = largeur fenetre/largeur brique
  pour 3 joueurs ou plus
    nb = */
void draw_brique(Brique *briques, int nb){
  int i;
  glBegin(GL_POLYGON);
  for (i = 0; i < nb; i++) {
    switch (briques[i].nb_cotes) {
      case 2:
        glColor3ub(briques[i].color.r, briques[i].color.g, briques[i].color.b);
        /*glTexCoord2f(0,0);*/
        glVertex2f(-(briques[i].largeur/2), briques[i].hauteur/2);
        /*glTexCoord2f(1,0);*/
        glVertex2f(briques[i].largeur/2, briques[i].hauteur/2);
        /*glTexCoord2f(1,1);*/
        glVertex2f(briques[i].largeur/2, -(briques[i].hauteur/2));
        /*glTexCoord2f(0,1);*/
        glVertex2f(-(briques[i].largeur/2), -(briques[i].hauteur/2));
        break;
      default:
        break;

    }
  }
  glEnd();
}
=======
#include "elements/brick.h"
>>>>>>> fefdfb7ca284ac11a0b6a56daa75664f46ac3d91:src/elements/brick.c
