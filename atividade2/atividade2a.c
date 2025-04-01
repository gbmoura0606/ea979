
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

unsigned char *popularity(Color *img, Color *histogram, int numPixels,
                          int numLevels) {
  unsigned char *finalImg = (unsigned char *)malloc(numPixels * 3);
  Color pixelLevel;

  for (int pixelIndex = 0; pixelIndex < numPixels; pixelIndex++) {
    float smallestDistance = 255 + 255 + 255 + 1;

    for (int i = 0; i < numLevels; i++) {
      float d = getColorDistance(img[pixelIndex], histogram[i]);

      if (d < smallestDistance) {
        smallestDistance = d;
        pixelLevel = histogram[i];
      }
    }

    finalImg[(pixelIndex * 3)] = pixelLevel.r;
    finalImg[(pixelIndex * 3) + 1] = pixelLevel.g;
    finalImg[(pixelIndex * 3) + 2] = pixelLevel.b;
  }

  return finalImg;
}

int main(int argc, char *argv[]) {
  int w, h, channels, numPixels, numColors;
  unsigned char *qtzdImg = stbi_load(argv[1], &w, &h, &channels, 3);
  Color *img = charIntoColor(qtzdImg, w, h), *histogram;

  numPixels = w * h;
  histogram = buildHistogram(img, numPixels, &numColors);

  qtzdImg = popularity(img, histogram, numPixels, numColors / 2);
  stbi_write_png("popularity_half.png", w, h, channels, qtzdImg, 0);

  qtzdImg = popularity(img, histogram, numPixels, numColors / 4);
  stbi_write_png("popularity_quarter.png", w, h, channels, qtzdImg, 0);

  free(img);
  free(histogram);
  free(qtzdImg);

  return 0;
}