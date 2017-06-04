#ifndef FONCTIONS_H_
#define FONCTIONS_H_


typedef enum { false, true } bool;

typedef enum { bas, droite, haut, gauche } sens;

typedef enum { start, game, end, rules } mode;

typedef enum { brick_normal, brick_ma_1, brick_ma_2, brick_bo_1, brick_bo_2,
               background, rules_screen, ending_screen, start_screen,
               button_quit, button_replay, button_return, button_rules,
               button_1p, button_2p, button_3p, button_4p
             } id_textures;
typedef enum {ball_sound, brick_sound, ending_sound } id_sounds;

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT  800
#define BIT_PER_PIXEL  32

void setVideoMode();
void reshape(unsigned int width, unsigned int height);
void load_images(SDL_Surface ** images);
void init_textures(SDL_Surface ** images, int nb_textures, GLuint * textures);
void free_textures(SDL_Surface ** images, int nb_textures, GLuint *textures);
#endif
