#include "color.h"
#include "histogram.h"
#include "sort.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Color getAvgColor(Color *colors, int numColors) {
  unsigned int rSum = 0, gSum = 0, bSum = 0, countSum = 0;
  Color avgColor;

  for (int i = 0; i < numColors; i++) {
    rSum = rSum + (colors[i].r * colors[i].count);
    gSum = gSum + (colors[i].g * colors[i].count);
    bSum = bSum + (colors[i].b * colors[i].count);

    countSum = countSum + colors[i].count;
  }

  if (countSum > 0) {
    avgColor.r = rSum / countSum;
    avgColor.g = gSum / countSum;
    avgColor.b = bSum / countSum;
  } else {
    avgColor.r = 0;
    avgColor.g = 0;
    avgColor.b = 0;
  }

  return avgColor;
}

Color *getLevels(Color *regionColors, int numRegionColors, Color *levels,
                 int numLevels, int *levelsIndex) {
  if (*levelsIndex >= numLevels) {
    return levels;
  }

  if (numRegionColors <= 1) {
    if (*levelsIndex < numLevels) {
      levels[*levelsIndex] = getAvgColor(regionColors, numRegionColors);
    }
    (*levelsIndex)++;
    return levels;
  }

  unsigned char biggestEdge = getBiggestEdge(regionColors, numRegionColors);
  sortByBiggestEdge(regionColors, numRegionColors, biggestEdge);

  int numColorsLeft = numRegionColors / 2;
  int numColorsRight = numRegionColors - numColorsLeft;

  getLevels(regionColors, numColorsLeft, levels, numLevels, levelsIndex);
  getLevels(regionColors + numColorsLeft, numColorsRight, levels, numLevels,
            levelsIndex);

  return levels;
}

unsigned char *medianCut(Color *img, Color *histogram, int numPixels,
                         int numColors, int numLevels) {
  unsigned char *finalImg = (unsigned char *)malloc(numPixels * 3);
  int levelsIndex = 0;

  Color *levels = (Color *)malloc(numLevels * sizeof(Color));
  getLevels(histogram, numColors, levels, numLevels, &levelsIndex);

  for (int i = 0; i < numLevels; i++) {
    printf("level %d:  r %u g %u b %u\n", i, levels[i].r, levels[i].g,
           levels[i].b);
  }

  for (int pixelIndex = 0; pixelIndex < numPixels; pixelIndex++) {
    Color pixelLevel = {0, 0, 0, 0};
    float smallestDistance = 255 + 255 + 255 + 1;

    for (int i = 0; i < numLevels; i++) {
      float d = getColorDistance(img[pixelIndex], levels[i]);

      if (d < smallestDistance) {
        smallestDistance = d;
        pixelLevel = levels[i];
      }
    }

    finalImg[(pixelIndex * 3)] = pixelLevel.r;
    finalImg[(pixelIndex * 3) + 1] = pixelLevel.g;
    finalImg[(pixelIndex * 3) + 2] = pixelLevel.b;
  }

  free(levels);

  return finalImg;
}

int main(int argc, char *argv[]) {
  int w, h, channels, numPixels, numColors;
  unsigned char *qtzdImg = stbi_load(argv[1], &w, &h, &channels, 3);
  Color *img = charIntoColor(qtzdImg, w, h), *histogram;

  numPixels = w * h;
  histogram = buildHistogram(img, numPixels, &numColors);

  qtzdImg = medianCut(img, histogram, numPixels, numColors, numColors / 2);
  stbi_write_png("medianCut_half.png", w, h, channels, qtzdImg, 0);

  // qtzdImg = medianCut(img, histogram, numPixels, numColors / 4);
  // stbi_write_png("mediancut_quarter.png", w, h, channels, qtzdImg, 0);

  free(img);
  free(histogram);
  free(qtzdImg);

  return 0;
}