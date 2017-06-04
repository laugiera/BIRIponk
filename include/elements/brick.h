#ifndef BRICK_H_
#define BRICK_H_

typedef enum { ON, OFF } state;

typedef enum { normal, ball_speed_slow, ball_speed_fast, life_bonus, life_malus } brick_type;

typedef struct _brick{
  struct _point3D position;
  float length;
  float height;
  brick_type type;
  state status;
  CustomColor color;
  int nb_vertex;
}Brick;

int get_nb_bricks(char *layout_file_path);
int init_bricks(Brick *bricks, int nb_players, char *layout_file_path);
void draw_bricks(Brick *bricks, int nb);

#endif
