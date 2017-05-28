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

void init_gameboard(Gameboard *board, int nb_players, char *layout_file_path){
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
    draw_life(&board.players[i]);
  }

}
