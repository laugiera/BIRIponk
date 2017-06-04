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
#include "elements/gameboard.h"

/**
 * initialise la structure gameboard passée en paramètre en fonction du nombre de joueurs
 * et du fichier de chargement des briques
 * important : les start_orientation et start_position des players doivent être définies
 * avant d'utiliser init_player()
 * @param board            pointeur sur une struct Gameboard
 * @param nb_players       nombre de joueurs dans la partie
 * @param layout_file_path chemin vers le fichier de chargement
 */
void init_gameboard(Gameboard *board, int nb_players, char * layout_file_path){
  int i;
  board->nb_players = nb_players;
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
  for(i=0; i<nb_players; i++){
    init_player(&(board->players[i]), i);
  }
  board->nb_bricks = get_nb_bricks(layout_file_path);
  board->bricks  = malloc(sizeof(Brick)*board->nb_bricks);
  if(!board->bricks)
    exit(1);
  init_bricks(board->bricks,1, nb_players, layout_file_path);
}

/**
 * Libère l'espace mémoire attribué au gameboard
 * @param board pointeur sur une struc Gameboard
 */
void free_gameboard(Gameboard *board){
  int i;
  for(i=0; i<board->nb_players; i++){
    free_player(&(board->players[i]));
  }
  free(board->players);
  free(board->bricks);
}

/**
 * Fonction générale d'affichage de tous les éléments du gameboard
 * @param board pointeur sur une struc Gameboard
 */
void draw_gameboard(Gameboard board){
    int i;
  draw_bricks(board.bricks, board.nb_bricks);
  for(i=0; i<board.nb_players; i++){
    draw_ball(*(board.players[i].ball));
    draw_bat(*(board.players[i].bat));
    draw_life(&board.players[i]);
  }
}

/**
 * Fonction générale de mise à jour de tous les éléments du gameboard
 * @param  board    pointeur sur une struc Gameboard
 * @param  keystate pointeur sur un tableau keystate SDL (voir doc SDL)
 * @return          l'id du gagnant de la partie, -1 si elle n'est pas terminée
 */
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
    if ( keystate['q'] )
      update_bat_position(board->players[1].bat,gauche);
    else if ( keystate['d'] )
      update_bat_position(board->players[1].bat,droite);
    else if (keystate['z'] && board->players[1].ball->speed == 0)
      board->players[1].ball->speed = 0.6;
    update_ball_position(board->players[1].ball, board);
  }

  return winner(board);
}

/**
 * Determine si la partie a été gagnée et par qui
 * @param  board pointeur sur une struc Gameboard
 * @return       l'id du gagnant de la partie, -1 si elle n'est pas terminée
 */
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

/**
 * Dessine le menu principal du jeu
 */
void draw_start_screen(){
  CustomColor c = color(255,255,225);
  /*background*/
  draw_rectangle(c,200,200);

  c = color(255,0,50);
  /*choixnb joueurs*/
  glPushMatrix();
  glTranslatef(-36,40,0);
  draw_rectangle(c,20,15);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-12,40,0);
  draw_rectangle(c,20,15);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(12,40,0);
  draw_rectangle(c,20,15);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(36,40,0);
  draw_rectangle(c,20,15);
  glPopMatrix();

  /*brules button*/
  draw_rectangle(c,20,100);

  /*quit button*/
  glPushMatrix();
  glTranslatef(0, -40,0);
  draw_rectangle(c,20,100);
  glPopMatrix();
}

void draw_rules_screen(){
  CustomColor c = color(255,255,225);
  /*background*/
  draw_rectangle(c,200,200);
  /*quit button*/
  c = color(255,0,50);
  glPushMatrix();
  glTranslatef(45,85,0);
  draw_rectangle(c,20,100);
  glPopMatrix();
  c = color(255,0,50);
}
void draw_end_screen(){
  CustomColor c = color(255,255,225);
  /*background*/
  draw_rectangle(c,200,200);

  c = color(255,0,50);
  /*replay button*/
  draw_rectangle(c,20,100);
  /*quit button*/
  glPushMatrix();
  glTranslatef(0, -40,0);
  draw_rectangle(c,20,100);
  glPopMatrix();
}
