#ifndef FONCTIONS_H_
#define FONCTIONS_H_

/*static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;*/
static const unsigned int BIT_PER_PIXEL = 32;

typedef enum { false, true } bool;

typedef enum { bas, haut } sens;


void setVideoMode();
void reshape(unsigned int width, unsigned int height);

#endif
