/**
 * Fonctions liées au gameboard
 */
 
#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

#include "elements/player.h"
#include "elements/brick.h"

typedef struct _gameboard{
  int nb_players;
  int nb_bricks;
  struct _player *players;
  struct _brick *bricks;
}Gameboard;

void init_gameboard(Gameboard *gb, int nb_players,char * layout_file_path);
void free_gameboard(Gameboard *gameboard);
void draw_gameboard(Gameboard board, GLuint * textures);
int update_gameboard(Gameboard *board, Uint8 *keystate);
int winner(Gameboard *board);

#endif
