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
#include "geometry/canonics.h"
#include "geometry/point_vect.h"
#include "fonctions.h"
#include "elements/gameboard.h"

void init_gameboard(Gameboard *board, int nb_players, char * layout_file_path){
  int i;
  board->nb_players = nb_players; /*max à définir*/
  board->players = malloc(sizeof(Player)*nb_players);
  if(!board->players){
    exit(1);
  }
  switch(nb_players){
    case 1:
      /*milieu en bas*/
      board->players[0].start_position = pointXY(0,-100);
      board->players[0].start_orientation = normalize(vectorXY(0,1));
      break;
    case 2:
      /*milieu en bas*/
      board->players[0].start_position = pointXY(0,-100);
      board->players[0].start_orientation = normalize(vectorXY(0,1));
      /*milieu en haut*/
      board->players[1].start_position = pointXY(0,100);
      board->players[1].start_orientation = normalize(vectorXY(0,-1));
      break;
    default:
      break;
  }
  CustomColor c =color(69,142,206);
  for(i=0; i<nb_players; i++){
    c.g = (c.g+30)%255;
    c.r = (c.r+30)%255;
    c.b = (c.b+30)%255;
    init_player(&(board->players[i]), i, c);
  }
  board->nb_bricks = get_nb_bricks(layout_file_path);
  board->bricks  = malloc(sizeof(Brick)*board->nb_bricks);
  if(!board->bricks)
    exit(1);
  init_bricks(board->bricks,1, nb_players, layout_file_path);
}

void free_gameboard(Gameboard *board){
  int i;
  for(i=0; i<board->nb_players; i++){
    free_player(&(board->players[i]));
  }
  free(board->players);
  free(board->bricks);
}

void draw_gameboard(Gameboard board, GLuint * textures){
  glEnable(GL_TEXTURE_2D);
  glColor4f(1.0, 1.0, 1.0, 1.0);
  CustomColor c = color(255,255,225);
  glBindTexture(GL_TEXTURE_2D, textures[background]);
  draw_rectangle(c,200,200);
  int i;
  draw_bricks(board.bricks, board.nb_bricks, textures);
  for(i=0; i<board.nb_players; i++){
    draw_ball(*(board.players[i].ball));
    draw_bat(*(board.players[i].bat));
    draw_life(&board.players[i]);
  }

    glDisable(GL_TEXTURE_2D);
}

int update_gameboard(Gameboard *board, Uint8 *keystate){
  /*Player 1*/
  if ( keystate[SDLK_LEFT]  )
    update_bat_position(board->players[0].bat,gauche);
  else if ( keystate[SDLK_RIGHT] )
    update_bat_position(board->players[0].bat,droite);
  else if (keystate[SDLK_UP] && board->players[0].ball->speed == 0)
    board->players[0].ball->speed = 0.6;
  update_ball_position(board->players[0].ball, board);

  if(board->nb_players >= 2){
  /*Player 2*/
    if ( keystate['a'] )
      update_bat_position(board->players[1].bat,gauche);
    else if ( keystate['z'] )
      update_bat_position(board->players[1].bat,droite);
    else if (keystate['s'] && board->players[1].ball->speed == 0)
      board->players[1].ball->speed = 0.6;
    update_ball_position(board->players[1].ball, board);
  }

  return winner(board);
}

int winner(Gameboard *board){
  int i, count=0, winner;
  if (board->nb_players == 1){
    return (board->players[0].life <= 0)? 0 : -1;
  }
  else {
    for(i=0; i<board->nb_players; i++){
      if(board->players[i].life >0){
        winner = i;
        ++ count;
      }
    }
    return (count == 1)? winner: -1;
  }

}

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
