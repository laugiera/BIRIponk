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

  Player p_bas, p_haut;

  init_player(&p_bas,1);
  init_player(&p_haut,2);

  /*BOUCLE D'AFFICHAGE*/
  int loop = 1;
  Uint8 *keystate = SDL_GetKeyState(NULL);

  while(loop) {
    Uint32 startTime = SDL_GetTicks();

    /*UPDATE*/
    update_position(p_bas.ball);

    if ( keystate['q'] )
      update_br_position(p_bas.barre,gauche);
    else if ( keystate['d'] )
      update_br_position(p_bas.barre,droite);
    else if ( keystate[SDLK_LEFT]  )
      update_br_position(p_haut.barre,gauche);
    else if ( keystate[SDLK_RIGHT] )
      update_br_position(p_haut.barre,droite);

    /*DESSIN*/
    glClear(GL_COLOR_BUFFER_BIT);
    /**/
    draw_ball(*p_bas.ball);
    draw_barre(*p_bas.barre);
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

  free_player(&p_bas);
  free_player(&p_haut);
  SDL_Quit();

  return EXIT_SUCCESS;
}
