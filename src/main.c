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
#include <SDL/SDL_mixer.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif
#include "fonctions.h"
#include "geometry/canonics.h"
#include "geometry/point_vect.h"
#include "elements/gameboard.h"

int main(int argc, char** argv) {

/*INIT--------------------------------------------------------------------------*/
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }
  setVideoMode();
  SDL_WM_SetCaption("BIRIPONG", NULL);

  /*VARIABLES*/
  Gameboard gb;
  int loop = 1; int mode = start;
  int nb_players = 0;
  Point2D mouse = pointXY(-100,-100);
  Uint8 *keystate = SDL_GetKeyState(NULL);
  /*TEXTURES*/
  int nb_textures = 17;
  SDL_Surface * images[nb_textures];
  GLuint textures[nb_textures];
  load_images(images);
  init_textures(images, nb_textures, textures);
  /*SOUND*/
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    printf("%s", Mix_GetError());
  Mix_Music *musique;
  musique = Mix_LoadMUS("ressources/musique.mp3");
  Mix_PlayMusic(musique, -1);
  Mix_VolumeMusic(MIX_MAX_VOLUME / 4);

/*MAIN LOOP--------------------------------------------------------------------------*/
  while(loop) {
    Uint32 startTime = SDL_GetTicks();
    /*START MENU--------------------------------------------------------------------------*/
    if (mode == start) {
      glClear(GL_COLOR_BUFFER_BIT);
       draw_start_screen(textures);
       SDL_GL_SwapBuffers();
      /*on compare avec les coord du clic ac ceux du bouton concerné*/
        if(mouse.x>=-45 && mouse.x<=-30 && mouse.y >=-50 && mouse.y <=-30){
          printf("GAME PLAYER 1\n" );
          nb_players = 1;
          mode = game;
          init_gameboard(&gb,nb_players,"ressources/level.txt");
          mouse = pointXY(-100,-100); /*réinitialise */
        }
        else if(mouse.x>=-20 && mouse.x<=-5 && mouse.y >=-50 && mouse.y <=-30){
          printf("GAME PLAYER 2\n" );
          nb_players = 2;
          mode = game;
          init_gameboard(&gb,nb_players,"ressources/level.txt");
          mouse = pointXY(-100,-100); /*réinitialise */
        }
        else if(mouse.x>=-50 && mouse.x<=50 && mouse.y >=-10 && mouse.y <=10){
          printf("RULE\n" );
          mode = rules;
          mouse = pointXY(-100,-100); /*réinitialise */
        }
        else if(mouse.x>=-50 && mouse.x<=50 && mouse.y >=30 && mouse.y <=50){
          printf("QUIT\n" );
          mode = -1;
        }
    }
    /*GAME---------------------------------------------------------------------------------*/
    else if (mode == game){

      /*UPDATE*/
      int winner = update_gameboard(&gb, keystate);
      /*DESSIN*/
      glClear(GL_COLOR_BUFFER_BIT);
      draw_gameboard(gb, textures);
      SDL_GL_SwapBuffers();
      /* ****** */
      if (winner!= -1) {
        printf("Le gagnant est le joueur %d !!!\n", winner+1);
        mode = end;
      }
    }
    /*ENDING MENU--------------------------------------------------------------------------*/
    else if (mode == end){
      glClear(GL_COLOR_BUFFER_BIT);
      draw_end_screen(textures);
      SDL_GL_SwapBuffers();
      if(mouse.x>=-50 && mouse.x<=50 && mouse.y >=-10 && mouse.y <=10){
        mode = start;
        mouse = pointXY(-100,-100); /*réinitialise */
      }
      else if(mouse.x>=-50 && mouse.x<=50 && mouse.y >=30 && mouse.y <=50){
        mode = -1;
      }
    }
    /*RULES MENU--------------------------------------------------------------------------*/
    else if (mode == rules){
      glClear(GL_COLOR_BUFFER_BIT);
      draw_rules_screen(textures);
      SDL_GL_SwapBuffers();
      if(mouse.x>=-5 && mouse.x<=95 && mouse.y >=-95 && mouse.y <=-75){
        mode = start;
      }
    }
    else if (mode == -1)
      loop = false;

    /*SDL EVENTS--------------------------------------------------------------------------*/
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
        case SDL_MOUSEBUTTONDOWN:
        mouse.x = (-1.0 + 2.0 *(float)e.button.x/WINDOW_WIDTH)*100;
        mouse.y = (-1.0 + 2.0 *(float)e.button.y/WINDOW_HEIGHT)*100;

          printf("%f %f\n",mouse.x,mouse.y );
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

/*FREE--------------------------------------------------------------------------*/
  if(nb_players != 0) free_gameboard(&gb);
  free_textures(images, nb_textures, textures);
  Mix_FreeMusic(musique);
  Mix_CloseAudio();
  SDL_Quit();

  return EXIT_SUCCESS;
}
