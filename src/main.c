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
#include "fonctions.h"
#include "geometry/canonics.h"
#include "geometry/point_vect.h"
#include "elements/ball.h"
#include "elements/player.h"
#include "elements/brique.h"
#include "elements/barre.h"

int main(int argc, char** argv) {
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }
  setVideoMode();
  SDL_WM_SetCaption("BIRIPONG", NULL);

  CustomColor vert = {100, 200, 0};
  Ball ballon;
  ballon.position = pointXY(0,0);
  ballon.diam = 40;
  ballon.color = vert;
  ballon.velocity = vectorXY(1,1);

  Barre barre_bas;
  barre_bas.hauteur = 10;
  barre_bas.largeur = 30;
  barre_bas.position = pointXY(0,-(100-(barre_bas.hauteur/2)));
  barre_bas.color = vert;
  barre_bas.velocity = vectorXY(1,1);

  Barre barre_haut;
  barre_haut.hauteur = 10;
  barre_haut.largeur = 30;
  barre_haut.position = pointXY(0,(100-(barre_haut.hauteur/2)));
  barre_haut.color = vert;
  barre_haut.velocity = vectorXY(1,1);

  /*BOUCLE D'AFFICHAGE*/
  int loop = 1;
  Uint8 *keystate = SDL_GetKeyState(NULL);

  while(loop) {
    Uint32 startTime = SDL_GetTicks();

    /*UPDATE*/
    update_position(&ballon);
    if ( keystate['q'] )
      update_br_position(&barre_bas,gauche);
    else if ( keystate['d'] )
      update_br_position(&barre_bas,droite);
    else if ( keystate[SDLK_LEFT]  )
      update_br_position(&barre_haut,gauche);
    else if ( keystate[SDLK_RIGHT] )
      update_br_position(&barre_haut,droite);

    /*DESSIN*/
    glClear(GL_COLOR_BUFFER_BIT);
    /**/
    /*draw_ball(ballon);*/
    draw_barre(barre_bas);
    draw_barre(barre_haut);
    /**/
    SDL_GL_SwapBuffers();
    /* ****** */

    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      switch(e.type) {
        case SDL_QUIT:
          loop=0;
          break;
        case SDL_KEYDOWN:
          switch (e.key.keysym.sym) {
            case SDLK_ESCAPE:
              loop = 0;
              break;
            default:
              break;
          }
          break;
        default:
          break;
      }
    }

    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < 1000/60) {
      SDL_Delay( 1000/60 - elapsedTime);
    }
  }

  SDL_Quit();

  return EXIT_SUCCESS;
}
