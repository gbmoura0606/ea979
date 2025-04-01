#include <stdio.h>
#include <stdlib.h>

unsigned char clamp(float valor) {
  if (valor < 0.0f)
    return 0;
  if (valor > 255.0f)
    return 255;
  return (unsigned char)valor;
}

int main() {
  int w = 4;
  int h = 4;

  unsigned char *img = malloc(w * h);

  for (int row = 0; row < h; row++) {
    for (int col = 0; col < w; col++) {
      int index = row * w + col;
      float value = (row + col) * 50.0f;
      img[index] = clamp(value);
    }
  }

  for (int row = 0; row < h; row++) {
    for (int col = 0; col < w; col++) {
      int idx = row * w + col;
      printf("%3d ", img[idx]);
    }
    printf("\n");
  }

  free(img);
  return 0;
}