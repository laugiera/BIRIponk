#ifndef FONCTIONS_H_
#define FONCTIONS_H_


typedef enum { false, true } bool;

typedef enum { bas, droite, haut, gauche } sens;

typedef enum { start, game, end, rules } mode;

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT  800
#define BIT_PER_PIXEL  32

void setVideoMode();
void reshape(unsigned int width, unsigned int height);

#endif
