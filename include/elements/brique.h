#ifndef BRIQUE_H_
#define BRIQUE_H_

typedef enum { ON, OFF } etat;

typedef enum { vitesse_lent, vitesse_rapide, vie_plus, vie_moins } bonus;

typedef struct _brique{
  struct _point3D position;
  float largeur;
  float hauteur;
  bonus alteration;
  etat vie;
}Brique;


#endif
