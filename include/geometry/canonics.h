#ifndef CANONICS_H_
#define CANONICS_H_

static const float PI = 3.1415926535;
static int SEGMT = 64;

typedef struct _customColor{
  int r,g,b;
}CustomColor;

void draw_circle(int full, CustomColor color);
void draw_square(int full, CustomColor color);
void draw_rounded_square(int full, float radius, CustomColor color);

#endif
