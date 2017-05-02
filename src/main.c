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
  ballon.position = pointXYZ(0,0,0);
  ballon.diam = 40;
  ballon.color = vert;
  ballon.velocity = vectorXYZ(1,1,0);


  /*BOUCLE D'AFFICHAGE*/
  int loop = 1;
  while(loop) {
    Uint32 startTime = SDL_GetTicks();

    /*UPDATE*/
    update_position(&ballon);

    /*DESSIN*/
    glClear(GL_COLOR_BUFFER_BIT);
    /**/
    draw_ball(ballon);
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
          if (e.key.keysym.sym == 'q' || e.key.keysym.sym == SDLK_ESCAPE) {
            loop = 0;
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
