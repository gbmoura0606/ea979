#include "histogram.h"
#include "color.h"
#include "sort.h"
#include <stdlib.h>

void insertColor(Color *histogram, Color c, int *numColors) {
  for (int i = 0; i < *numColors; i++) {
    if (isSameColor(histogram[i], c)) {
      histogram[i].count++;
      return;
    }
  }

  histogram[*numColors].r = c.r;
  histogram[*numColors].g = c.g;
  histogram[*numColors].b = c.b;
  histogram[*numColors].count = 1;
  (*numColors)++;
}

Color *buildHistogram(Color *img, int nPixels, int *numColors) {
  Color *histogram = (Color *)malloc(nPixels * sizeof(Color));
  *numColors = 0;

  for (int i = 0; i < nPixels; i++) {
    insertColor(histogram, img[i], numColors);
  }

  qsort(histogram, nPixels, sizeof(Color),
        (int (*)(const void *, const void *))compareByCount);

  return histogram;
}
