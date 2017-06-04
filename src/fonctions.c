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


void setVideoMode() {
  if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  reshape(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void reshape(unsigned int width, unsigned int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-100., 100., -100., 100.);
}

void load_images(SDL_Surface ** images){
  images[brick_normal] = IMG_Load("ressources/brick_normal.jpg");
  images[brick_ma_1] = IMG_Load("ressources/brick_ma_1.jpg");
  images[brick_ma_2] = IMG_Load("ressources/brick_ma_2.jpg");
  images[brick_bo_1] = IMG_Load("ressources/brick_bo_1.jpg");
  images[brick_bo_2] = IMG_Load("ressources/brick_bo_2.jpg");
  images[background] = IMG_Load("ressources/background.png");
  images[rules_screen] = IMG_Load("ressources/rules_screen.png");
  images[ending_screen] = IMG_Load("ressources/ending_screen.png");
  images[start_screen] = IMG_Load("ressources/start_screen.png");
  images[button_quit] = IMG_Load("ressources/button_quit.png");
  images[button_replay] = IMG_Load("ressources/button_replay.png");
  images[button_return] = IMG_Load("ressources/button_return.png");
  images[button_rules] = IMG_Load("ressources/button_rules.png");
  images[button_1p] = IMG_Load("ressources/button_1p.png");
  images[button_2p] = IMG_Load("ressources/button_2p.png");
  images[button_3p] = IMG_Load("ressources/button_3p.png");
  images[button_4p] = IMG_Load("ressources/button_4p.png");
}

void init_textures(SDL_Surface ** images, int nb_textures, GLuint * textures){
  int i;
  glEnable(GL_TEXTURE_2D);
  glGenTextures(nb_textures,textures);
  for (i = brick_normal; i < nb_textures; i++){
      glBindTexture(GL_TEXTURE_2D,textures[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      GLenum format;
      switch (images[i]->format->BytesPerPixel) {
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
          exit(0);
          break;
        }
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, images[i]->w, images[i]->h, 0, format, GL_UNSIGNED_BYTE, images[i]->pixels);
      glBindTexture(GL_TEXTURE_2D,0);
  }
}

void free_textures(SDL_Surface ** images, int nb_textures, GLuint *textures){
  int i;
  for (i = brick_normal; i < nb_textures; i++){
      SDL_FreeSurface(images[i]);
      glBindTexture(GL_TEXTURE_2D,0);
  }
  glDeleteTextures(nb_textures,textures);

}
