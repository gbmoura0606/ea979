#include <stdio.h>
#include <stdlib.h>

float getHue(float r, float g, float b, float min, float max) {
  float hue;

  if (max == r) {
    hue = 60 * (g - b) / (max - min);
  } else if (max == g) {
    hue = 60 * (b - r) / (max - min) + 120;
  } else {
    hue = 60 * (r - g) / (max - min) + 240;
  }

  if (hue >= 360)
    hue = hue - 360;

  return (hue >= 0 ? hue : hue + 360);
}

float getSaturation(float min, float max) {
  if (max == 0)
    return 0;

  return (max - min) / max;
}

int main() {
  printf("%f\n", getHue(1, 1, 0, 0, 1));
  printf("%f\n", getSaturation(0, 1));
  printf("%f\n", 1);

  unsigned char *imgH = malloc(216 * 216);
  unsigned char *imgS = malloc(216 * 216);
  unsigned char *imgV = malloc(216 * 216);

  int posIndex, index;
  float hue, saturation, value;

  for (int row = 0; row < 216; row++) {
    for (int col = 0; col < 216; col++) {
      posIndex = (row * 216 + col);
      index = (row * 216 + col) * 3;

      imgH[posIndex] = (hue / 360) * 255;
      imgS[posIndex] = saturation * 255;
      imgV[posIndex] = value * 255;
    }
  }

  // for (int i = 0; i < 216 * 216; i++) {
  //   printf("%d ", imgH[i]);
  // }

  printf("%f", getHue(1, 0, 1, 0, 1) / 360 * 255);
  return 0;
}