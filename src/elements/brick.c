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
#include "geometry/canonics.h"
#include "geometry/point_vect.h"
#include "fonctions.h"
#include "elements/brick.h"

int get_nb_bricks(char *layout_file_path){
  /*charge le fichier de briques*/
  FILE * level_file = NULL;

  level_file = fopen(layout_file_path,"r+");
  if(level_file == NULL)
    exit(1);

  int rows, cols, b = 0;
  fscanf(level_file,"%d %d",&rows,&cols);
  fclose(level_file);
  return rows*cols;
}

int init_bricks(Brick *bricks, int level, int nb_players, char *layout_file_path){
  /*charge le fichier de briques*/
  FILE * level_file = NULL;

  level_file = fopen(layout_file_path,"r+");
  if(level_file == NULL)
    exit(1);

  int rows, cols, b=0;
  fscanf(level_file,"%d %d",&rows,&cols);
  int nb_bricks = rows*cols;
  int i = 0;
  float length = (float)200/cols;
  float height = (float)length/2;
  float W = ((float)-200/2) + ((float)length/2);
  float H = ((float)rows-1)*((float)height/2);
  while(b != EOF){
    b = fgetc(level_file);
    if(b != ' ' && b != '\n' && b != -1){
        switch (b) {
          case '0':
            bricks[i].color = color(6,51,95);
            bricks[i].type = normal; /*bleu*/
            break;
          case '1':
            bricks[i].color = color(240,128,0);
            bricks[i].type = ball_speed_slow;
            break;  /*orange*/
          case '2':
            bricks[i].color = color(0,208,240);
            bricks[i].type = ball_speed_fast;
            break;  /*cyan*/
          case '3':
            bricks[i].color = color(81,210,26);
            bricks[i].type = life_bonus;
            break; /*vert*/
          case '4':
            bricks[i].color = color(255,0,0);
            bricks[i].type = life_malus;
            break;  /*rouge*/
          default :
            break;
        }

        bricks[i].length = length;
        bricks[i].height = height;
        bricks[i].status = ON;
        printf("W %f H %f de %d\n",W,H,i);
        bricks[i].position = pointXY(W,H);

        (bricks+i)->nb_vertex = nb_players <= 2 ? 4:3; /*rectangle si 2 joueurs, triangles si plus*/
        if(W+length >= 200/2){
          W = ((float)-200/2) + ((float)length/2);
          H -= height;
        }
        else
          W += length;
        i++;
    }
  }
  fclose(level_file);
  return nb_bricks;
}

void draw_bricks(Brick *bricks, int nb, GLuint * textures){
  int i;
  for (i = 0; i < nb; i++) {
    switch (bricks[i].nb_vertex) {
      case 4:
        if(bricks[i].status == ON){
          glEnable(GL_TEXTURE_2D);
          glColor4f(1.0, 1.0, 1.0, 1.0);
          switch (bricks[i].type) {
            case brick_normal:
                  glBindTexture(GL_TEXTURE_2D, textures[brick_normal]);
                  break;
            case brick_bo_1 :
                  glBindTexture(GL_TEXTURE_2D, textures[brick_bo_1]);
                  break;
            case brick_bo_2 :
                  glBindTexture(GL_TEXTURE_2D, textures[brick_bo_2]);
                  break;
            case brick_ma_1 :
                  glBindTexture(GL_TEXTURE_2D, textures[brick_ma_1]);
                  break;
            case brick_ma_2 :
                  glBindTexture(GL_TEXTURE_2D, textures[brick_ma_2]);
                  break;
            default:
                  glBindTexture(GL_TEXTURE_2D, textures[brick_normal]);
                  break;
          }

          glBegin(GL_POLYGON);
          /*glColor3ub(bricks[i].color.r, bricks[i].color.g, bricks[i].color.b);*/
          glTexCoord2f(0,0);
          glVertex2f(0.5 + bricks[i].position.x-(bricks[i].length/2), -0.5  + bricks[i].position.y+bricks[i].height/2);
          glTexCoord2f(1,0);
          glVertex2f(-0.5 + bricks[i].position.x+bricks[i].length/2, -0.5 + bricks[i].position.y+bricks[i].height/2);
          glTexCoord2f(1,1);
          glVertex2f(-0.5 + bricks[i].position.x+bricks[i].length/2, 0.5 + bricks[i].position.y-(bricks[i].height/2));
          glTexCoord2f(0,1);
          glVertex2f(0.5 + bricks[i].position.x-(bricks[i].length/2), 0.5 + bricks[i].position.y-(bricks[i].height/2));
          glEnd();

          glDisable(GL_TEXTURE_2D);
        }
        break;
      default:
        break;

    }
  }
}
