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
#include "fonctions.h"
#include "geometry/canonics.h"
#include "geometry/point_vect.h"
#include "elements/gameboard.h"

int main(int argc, char** argv) {
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }
  setVideoMode();
  SDL_WM_SetCaption("BIRIPONG", NULL);

  /* depreciated
  Player p_bas, p_haut;
  init_player(&p_bas,1);
  init_player(&p_haut,2);
  */
 Gameboard gb;
 init_gameboard(&gb,2);

  /*TEXTURE*/
  /*SDL_Surface * img = IMG_Load("img/gintama.jpg");
  int i,nb_textures = 3;
  GLuint textures[nb_textures];
  glEnable(GL_TEXTURE_2D);
  glGenTextures(nb_textures,textures);
  for (i = 0; i < nb_textures; i++){
      glBindTexture(GL_TEXTURE_2D,textures[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      GLenum format;
      switch (img->format->BytesPerPixel) {
        case 1:
          format=GL_RED;
          break;
        case 3:
          format = GL_RGB;
          break;
        case 4:
          format = GL_RGBA;

          break;
        default:
          fprintf(stderr, "Format des pixels de l’image  non pris en charge\n");
          return EXIT_FAILURE;
        }
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, format, GL_UNSIGNED_BYTE, img->pixels);
      glBindTexture(GL_TEXTURE_2D,0);
    }*/

  /*BOUCLE D'AFFICHAGE*/
  int loop = 1;
  Uint8 *keystate = SDL_GetKeyState(NULL);

  while(loop) {
    Uint32 startTime = SDL_GetTicks();

    /*UPDATE*/
    int winner = update_gameboard(&gb, keystate);
    if (winner!= -1) {printf("Le gagnant est le joueur %d !!!\n", winner+1);}

    /*DESSIN*/
    glClear(GL_COLOR_BUFFER_BIT);
    /*
    glPushMatrix();
    glScalef(60,60,0);

    glEnable(GL_TEXTURE_2D);
    glColor4f(1.0, 1.0, 1.0, 1.0);

    glBegin(GL_QUADS);
    glTexCoord2f(0,0);     glVertex2f(1, 1);
    glTexCoord2f(0,1);    glVertex2f(1, -1);
    glTexCoord2f(1,1);    glVertex2f(-1, -1);
    glTexCoord2f(1,0);    glVertex2f(-1, 1);
    glEnd();

    glPopMatrix();*/
    /* affichage pour les textures
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    draw_ball(*gb.players[0].ball);
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    draw_bat(*gb.players[0].bat);
    */

    /* affichage sans les textures, il faudrait pouvoir adapter les textures à ça
    surement que passer le tableau de textures en paramètres suffit mais dans le doute je touche pas
    */
    draw_gameboard(gb);

    /*glDisable(GL_TEXTURE_2D);*/

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

  /*FREE*/

  /*SDL_FreeSurface(img);
  for (i = 0; i < nb_textures; i++)
    glBindTexture(GL_TEXTURE_2D,0);
  glDeleteTextures(nb_textures,textures);*/

  free_gameboard(&gb);
  SDL_Quit();

  return EXIT_SUCCESS;
}
