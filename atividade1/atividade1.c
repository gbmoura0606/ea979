#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define W 216
#define H 216

unsigned char *openImage(int w, int h) {
  return stbi_load("image1.png", &w, &h, NULL, 0);
}

float minFloat(float a, float b, float c) {
  float menor = a;

  if (b < menor)
    menor = b;
  if (c < menor)
    menor = c;

  return menor;
}

float maxFloat(float a, float b, float c) {
  float maior = a;

  if (b > maior)
    maior = b;
  if (c > maior)
    maior = c;

  return maior;
}

float normalize(unsigned char v) { return v / 255.0f; }

float getHue(float r, float g, float b, float min, float max) {
  float hue;

  if (max == min)
    return 0;

  if (max == r)
    hue = 60 * (g - b) / (max - min);
  else if (max == g)
    hue = 60 * (b - r) / (max - min) + 120;
  else
    hue = 60 * (r - g) / (max - min) + 240;

  return (hue >= 0 ? hue : hue + 360);
}

float getSaturation(float min, float max) {
  if (max == 0)
    return 0;

  return (max - min) / max;
}

void extractRGB(unsigned char *img) {
  unsigned char *imgR = malloc(W * H);
  unsigned char *imgG = malloc(W * H);
  unsigned char *imgB = malloc(W * H);
  int posIndex, index;

  for (int row = 0; row < H; row++) {
    for (int col = 0; col < W; col++) {
      posIndex = (row * W + col);
      index = (row * W + col) * 3;

      imgR[posIndex] = img[index];
      imgG[posIndex] = img[index + 1];
      imgB[posIndex] = img[index + 2];
    }
  }

  stbi_write_png("image1_red.png", W, H, 1, imgR, 0);
  stbi_write_png("image1_green.png", W, H, 1, imgG, 0);
  stbi_write_png("image1_blue.png", W, H, 1, imgB, 0);

  free(imgR);
  free(imgG);
  free(imgB);
}

void extractCMY(unsigned char *img) {
  unsigned char *imgC = malloc(W * H);
  unsigned char *imgM = malloc(W * H);
  unsigned char *imgY = malloc(W * H);
  int posIndex, index;

  for (int row = 0; row < H; row++) {
    for (int col = 0; col < W; col++) {
      posIndex = (row * W + col);
      index = (row * W + col) * 3;

      imgC[posIndex] = 255 - img[index];
      imgM[posIndex] = 255 - img[index + 1];
      imgY[posIndex] = 255 - img[index + 2];
    }
  }

  stbi_write_png("image1_cyan.png", W, H, 1, imgC, 0);
  stbi_write_png("image1_magenta.png", W, H, 1, imgM, 0);
  stbi_write_png("image1_yellow.png", W, H, 1, imgY, 0);

  free(imgC);
  free(imgM);
  free(imgY);
}

void extractHSV(unsigned char *img) {
  unsigned char *imgH = malloc(W * H);
  unsigned char *imgS = malloc(W * H);
  unsigned char *imgV = malloc(W * H);
  int posIndex, index;
  float hue, saturation, value;

  for (int row = 0; row < H; row++) {
    for (int col = 0; col < W; col++) {
      posIndex = (row * W + col);
      index = (row * W + col) * 3;

      float r = normalize(img[index]);
      float g = normalize(img[index + 1]);
      float b = normalize(img[index + 2]);
      float min = minFloat(r, g, b);
      float max = maxFloat(r, g, b);

      hue = getHue(r, g, b, min, max);
      saturation = getSaturation(min, max);
      value = max;

      imgH[posIndex] = (unsigned char)(hue * 255 / 360);
      imgS[posIndex] = (unsigned char)(saturation * 255);
      imgV[posIndex] = (unsigned char)(value * 255);
    }
  }

  stbi_write_png("image1_hue.png", W, H, 1, imgH, 0);
  stbi_write_png("image1_saturation.png", W, H, 1, imgS, 0);
  stbi_write_png("image1_value.png", W, H, 1, imgV, 0);

  free(imgH);
  free(imgS);
  free(imgV);
}

int main() {
  unsigned char *img = openImage(W, H);

  if (!img) {
    printf("%s", stbi_failure_reason());
    return -1;
  }

  extractRGB(img);
  extractCMY(img);
  extractHSV(img);

  stbi_image_free(img);

  return 0;
}