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

void init_gameboard(Gameboard *board, int nb_players){
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
  for(i=0; i<nb_players; i++){
    init_player(&(board->players[i]), i);
  }
  board->nb_bricks = get_nb_bricks();
  board->bricks  = malloc(sizeof(Brick)*board->nb_bricks);
  if(!board->bricks)
    exit(1);
  init_bricks(board->bricks,1, nb_players);
}

void free_gameboard(Gameboard *board){

  int i;
  for(i=0; i<board->nb_players; i++){
    free_player(&(board->players[i]));
  }
  free(board->players);
  free(board->bricks);
}

void draw_gameboard(Gameboard board){
    int i;
  draw_bricks(board.bricks, board.nb_bricks);
  for(i=0; i<board.nb_players; i++){
    draw_ball(*(board.players[i].ball));
    draw_bat(*(board.players[i].bat));
  }
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
  /*
    if ( keystate['q'] )
      update_bat_position(board->players[1].bat,gauche);
    else if ( keystate['d'] )
      update_bat_position(board->players[1].bat,droite);
    else if (keystate['z'] && board->players[1].ball->speed == 0)
      board->players[1].ball->speed = 0.6;
    update_ball_position(board->players[1].ball, board);
  */
  /*AI*/
    update_bat_position_AI(board->players[1].bat, board);
    update_ball_position_AI(board->players[1].ball, board);
  }

  return winner(board);
}

int winner(Gameboard *board){
  int i, count=0, winner;
  for(i=0; i<board->nb_players; i++){
    if(board->players[i].life >0){
      winner = i;
      ++ count;
    }
  }
  return (count == 1)? winner: -1;
}
