/**
 * Fonctions d'initialisation SDL, gestions des textures et des menus
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
#include <SDL/SDL_mixer.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif
#include "fonctions.h"
#include "geometry/canonics.h"

/**
 * Ouvre une fenetre en utilisant la bibliothèque SDL
 */
void setVideoMode() {
  if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  reshape(WINDOW_WIDTH, WINDOW_HEIGHT);
}

/**
 * Inscrit un repère global (-100, 100, -100, 100) dans la fenêtre SDL
 * @param width  int largeur de la fenêtre
 * @param height int hauteur de la fenêtre
 */
void reshape(unsigned int width, unsigned int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-100., 100., -100., 100.);
}

/**
 * Charge les images de textures dans des surfaces SDL
 * @param images SDL_Surface ** tableaux de surfaces SDL
 */
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

/**
 * Initialise les textures OPENGL
 * @param images SDL_Surface ** tableaux de surfaces SDL
 * @param nb_textures int nombres de textures à charger
 * @param textures GLuint * tableau des identifiants OPENGL de textures
 */
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

/**
 * Libère les textures OPENGL et les surfaces SDL
 * @param images SDL_Surface ** tableaux de surfaces SDL
 * @param nb_textures int nombres de textures à charger
 * @param textures GLuint * tableau des identifiants OPENGL de textures
 */
void free_textures(SDL_Surface ** images, int nb_textures, GLuint *textures){
  int i;
  for (i = brick_normal; i < nb_textures; i++){
      SDL_FreeSurface(images[i]);
      glBindTexture(GL_TEXTURE_2D,0);
  }
  glDeleteTextures(nb_textures,textures);

}

/**
 * Dessine le menu principal du jeu
* @param textures GLuint * tableau des identifiants OPENGL de textures
 */
void draw_start_screen(GLuint * textures){
  glEnable(GL_TEXTURE_2D);
  glColor4f(1.0, 1.0, 1.0, 1.0);
  CustomColor c = color(255,255,225);
  /*background*/
  glBindTexture(GL_TEXTURE_2D, textures[start_screen]);
  draw_rectangle(c,200,200);
  glBindTexture(GL_TEXTURE_2D, 0);
  /*choixnb joueurs*/
  glBindTexture(GL_TEXTURE_2D, textures[button_1p]);
  glPushMatrix();
  glTranslatef(-36,40,0);
  draw_rectangle(c,20,15);
  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D, 0);
  /*choixnb joueurs*/
  glBindTexture(GL_TEXTURE_2D, textures[button_2p]);
  glPushMatrix();
  glTranslatef(-12,40,0);
  draw_rectangle(c,20,15);
  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D, 0);
  /*choixnb joueurs*/
  glBindTexture(GL_TEXTURE_2D, textures[button_3p]);
  glPushMatrix();
  glTranslatef(12,40,0);
  draw_rectangle(c,20,15);
  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D, 0);
  /*choixnb joueurs*/
  glBindTexture(GL_TEXTURE_2D, textures[button_4p]);
  glPushMatrix();
  glTranslatef(36,40,0);
  draw_rectangle(c,20,15);
  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D, 0);
  /*rules button*/
  glBindTexture(GL_TEXTURE_2D, textures[button_rules]);
  draw_rectangle(c,20,100);
  glBindTexture(GL_TEXTURE_2D, 0);
  /*quit button*/
  glBindTexture(GL_TEXTURE_2D, textures[button_quit]);
  glPushMatrix();
  glTranslatef(0, -40,0);
  draw_rectangle(c,20,100);
  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D, 0);

  glDisable(GL_TEXTURE_2D);
}

/**
 * Dessine le menu de régles de jeu
 * @param textures GLuint * tableau des identifiants OPENGL de textures
 */
void draw_rules_screen(GLuint *textures){
  glEnable(GL_TEXTURE_2D);
  glColor4f(1.0, 1.0, 1.0, 1.0);

  CustomColor c = color(255,255,225);
  /*background*/
  glBindTexture(GL_TEXTURE_2D, textures[rules_screen]);
  draw_rectangle(c,200,200);
  /*return button*/
  glBindTexture(GL_TEXTURE_2D, textures[button_return]);
  glPushMatrix();
  glTranslatef(45,85,0);
  draw_rectangle(c,20,100);
  glPopMatrix();

  glDisable(GL_TEXTURE_2D);
}

/**
 * TDessine le menu de fin de jeu
 * @param textures GLuint * tableau des identifiants OPENGL de textures
 */
void draw_end_screen(GLuint *textures){
  glEnable(GL_TEXTURE_2D);
  glColor4f(1.0, 1.0, 1.0, 1.0);

  CustomColor c = color(255,255,225);
  /*background*/
  glBindTexture(GL_TEXTURE_2D, textures[ending_screen]);
  draw_rectangle(c,200,200);
  /*replay button*/
  glBindTexture(GL_TEXTURE_2D, textures[button_replay]);
  draw_rectangle(c,20,100);
  /*quit button*/
  glBindTexture(GL_TEXTURE_2D, textures[button_quit]);
  glPushMatrix();
  glTranslatef(0, -40,0);
  draw_rectangle(c,20,100);
  glPopMatrix();

  glDisable(GL_TEXTURE_2D);
}
