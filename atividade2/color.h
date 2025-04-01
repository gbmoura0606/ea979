#ifndef COLOR_H
#define COLOR_H

typedef struct {
  unsigned char r, g, b;
  int count;
} Color;

int isSameColor(Color c1, Color c2);
float getColorDistance(Color c1, Color c2);
unsigned char getBiggestEdge(Color *img, int numPixels);
Color *charIntoColor(unsigned char *img, int w, int h);
Color *sortByBiggestEdge(Color *img, int numPixels, unsigned char edge);

#endif
