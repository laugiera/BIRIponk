#ifndef BRIQUE_H_
#define BRIQUE_H_

typedef enum { ON, OFF } etat;

typedef enum { vitesse_lent, vitesse_rapide, vie_plus, vie_moins } bonus;

typedef struct _brique{
  struct _point3D position;
  int nb_cotes;
  bonus alteration;
  etat vie;
  CustomColor color; 
}Brique;

void init_brique(Brique *b);
void draw_brique(Brique b, int nb);

#endif
