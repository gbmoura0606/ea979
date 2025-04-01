#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include "color.h"

void insertColor(Color *hist, Color c, int *nUniqueColors);
Color *buildHistogram(Color *img, int nPixels, int *nUniqueColors);

#endif
