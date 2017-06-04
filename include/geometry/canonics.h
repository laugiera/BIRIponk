/**
 * Fonctions pour les couleurs et dessin de composantes cercles et rectangles
 */

#ifndef CANONICS_H_
#define CANONICS_H_

typedef struct _customColor{
  int r,g,b;
}CustomColor;

CustomColor color(int r, int g, int b);
void draw_circle(int full, CustomColor color);
void draw_rectangle(CustomColor color, float hauteur, float largeur);

#endif
