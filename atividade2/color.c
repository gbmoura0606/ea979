#include "color.h"
#include "sort.h"
#include <stdlib.h>

Color *charIntoColor(unsigned char *img, int w, int h) {
  Color *colorImg = (Color *)malloc(w * h * sizeof(Color));

  for (int i = 0; i < w * h; i++) {
    colorImg[i].r = img[(i * 3)];
    colorImg[i].g = img[(i * 3) + 1];
    colorImg[i].b = img[(i * 3) + 2];
  }

  return colorImg;
}

int isSameColor(Color c1, Color c2) {
  if ((c1.r == c2.r) && (c1.g == c2.g) && (c1.b == c2.b))
    return 1;

  return 0;
}

float getColorDistance(Color c1, Color c2) {
  return abs(c1.r - c2.r) + abs(c1.g - c2.g) + abs(c1.b - c2.b);
}

unsigned char getBiggestEdge(Color *img, int numPixels) {
  int max[3] = {0, 0, 0};
  int min[3] = {255, 255, 255};

  for (int i = 0; i < numPixels; i++) {
    if (img[i].r > max[0])
      max[0] = img[i].r;

    if (img[i].g > max[1])
      max[1] = img[i].g;

    if (img[i].b > max[2])
      max[2] = img[i].b;

    if (img[i].r < min[0])
      min[0] = img[i].r;

    if (img[i].g < min[1])
      min[1] = img[i].g;

    if (img[i].b < min[2])
      min[2] = img[i].b;
  }

  unsigned char biggestEdge = 'r';
  if ((max[1] - min[1]) > (max[0] - min[0]))
    biggestEdge = 'g';
  if ((max[2] - min[2]) > biggestEdge)
    biggestEdge = 'b';

  return biggestEdge;
}

Color *sortByBiggestEdge(Color *img, int numPixels, unsigned char edge) {
  if (edge == 'r')
    qsort(img, numPixels, sizeof(Color),
          (int (*)(const void *, const void *))compareByR);

  if (edge == 'g')
    qsort(img, numPixels, sizeof(Color),
          (int (*)(const void *, const void *))compareByG);

  if (edge == 'b')
    qsort(img, numPixels, sizeof(Color),
          (int (*)(const void *, const void *))compareByB);

  return img;
}
