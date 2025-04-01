/*
 * Setup Version: Color Quantization Template
 * --------------------------------------------
 *
 * This template is designed to help you structure your program for the lab activity.
 * You must implement two algorithms:
 *
 * 1. Popularity Algorithm:
 *    - Build a histogram of the image’s colors.
 *    - Sort the histogram by frequency.
 *    - Use the top "targetColors" to create a palette.
 *    - Replace each pixel with the nearest palette color (using Euclidean distance).
 *
 * 2. Median Cut Algorithm:
 *    - Build a histogram of unique colors.
 *    - Recursively partition the color space (choose the channel with the largest range)
 *      until you reach the desired number of color boxes.
 *    - Compute a representative color for each box (using a weighted average).
 *    - Replace each pixel with the representative color from the corresponding box.
 *
 * Two output images should be produced for each algorithm:
 *    - One with half the original number of colors.
 *    - One with a quarter of the original number of colors.
 *
 * Compile with:
 *    gcc -o quantize setup_version.c -lm
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <math.h>
 
 // Include the STB image libraries for file I/O.
 #define STB_IMAGE_IMPLEMENTATION
 #include "stb_image.h"
 #define STB_IMAGE_WRITE_IMPLEMENTATION
 #include "stb_image_write.h"
 
 /* ===========================================================
    Data Structures & Function Prototypes
    =========================================================== */
 
 /* ColorEntry:
  *   - Represents an RGB color and its frequency in the image.
  */
 typedef struct {
     unsigned char r, g, b;
     int count;
 } ColorEntry;
 
 /* Function Prototypes:
  *   - add_or_update_color: Updates the histogram with a given color.
  *   - build_histogram: Constructs a histogram of unique colors from the image.
  *   - apply_popularity_quantization: (Placeholder) Implement the Popularity algorithm.
  *   - apply_mediancut_quantization: (Placeholder) Implement the Median Cut algorithm.
  *   - save_image: Saves an image to disk.
  */
 int add_or_update_color(ColorEntry **hist, int *n, unsigned char r, unsigned char g, unsigned char b);
 ColorEntry* build_histogram(unsigned char* data, int width, int height, int channels, int* uniqueCount);
 unsigned char* apply_popularity_quantization(unsigned char* data, int width, int height, int channels, int targetColors);
 unsigned char* apply_mediancut_quantization(unsigned char* data, int width, int height, int channels, int targetColors);
 void save_image(const char* filename, unsigned char* data, int width, int height, int channels);
 
 /* ===========================================================
    Main Function
    =========================================================== */
 int main(int argc, char* argv[]) {
     if (argc < 2) {
          fprintf(stderr, "Usage: %s <input_image>\n", argv[0]);
          return 1;
     }
     
     // Load the image in RGB mode (3 channels)
     int width, height, channels;
     unsigned char* data = stbi_load(argv[1], &width, &height, &channels, 3);
     if (!data) {
          fprintf(stderr, "Error loading image %s\n", argv[1]);
          return 1;
     }
     
     // Build a histogram to count unique colors
     int uniqueCount;
     ColorEntry* hist = build_histogram(data, width, height, channels, &uniqueCount);
     printf("Found %d unique colors in the image.\n", uniqueCount);
     free(hist);
     
     // Define target palette sizes (half and quarter reduction)
     int halfColors = uniqueCount / 2;
     int quarterColors = uniqueCount / 4;
     printf("Palette sizes: %d (half reduction), %d (quarter reduction).\n", halfColors, quarterColors);
     
     /* ---------- Popularity Algorithm ---------- */
     // TODO: Implement the Popularity algorithm in apply_popularity_quantization.
     unsigned char* popularity_half = apply_popularity_quantization(data, width, height, channels, halfColors);
     save_image("popularity_half.png", popularity_half, width, height, channels);
     free(popularity_half);
     
     unsigned char* popularity_quarter = apply_popularity_quantization(data, width, height, channels, quarterColors);
     save_image("popularity_quarter.png", popularity_quarter, width, height, channels);
     free(popularity_quarter);
     
     /* ---------- Median Cut Algorithm ---------- */
     // TODO: Implement the Median Cut algorithm in apply_mediancut_quantization.
     unsigned char* mediancut_half = apply_mediancut_quantization(data, width, height, channels, halfColors);
     save_image("mediancut_half.png", mediancut_half, width, height, channels);
     free(mediancut_half);
     
     unsigned char* mediancut_quarter = apply_mediancut_quantization(data, width, height, channels, quarterColors);
     save_image("mediancut_quarter.png", mediancut_quarter, width, height, channels);
     free(mediancut_quarter);
     
     stbi_image_free(data);
     return 0;
 }
 
 
 /* ===========================================================
    Histogram Functions
    =========================================================== */
 
 /*
  * add_or_update_color:
  *   Checks if the color (r, g, b) exists in the histogram.
  *   If it does, increments the count; otherwise, adds a new entry.
  */
 int add_or_update_color(ColorEntry **hist, int *n, unsigned char r, unsigned char g, unsigned char b) {
     for (int i = 0; i < *n; i++) {
          if ((*hist)[i].r == r && (*hist)[i].g == g && (*hist)[i].b == b) {
              (*hist)[i].count++;
              return i;
          }
     }
     *hist = realloc(*hist, (*n + 1) * sizeof(ColorEntry));
     if (*hist == NULL) {
          fprintf(stderr, "Memory allocation error in histogram creation.\n");
          exit(1);
     }
     (*hist)[*n].r = r;
     (*hist)[*n].g = g;
     (*hist)[*n].b = b;
     (*hist)[*n].count = 1;
     (*n)++;
     return *n - 1;
 }
 
 /*
  * build_histogram:
  *   Constructs a histogram from the image data.
  *   Returns an array of ColorEntry and sets uniqueCount.
  */
 ColorEntry* build_histogram(unsigned char* data, int width, int height, int channels, int* uniqueCount) {
     ColorEntry* hist = NULL;
     *uniqueCount = 0;
     int totalPixels = width * height;
     for (int i = 0; i < totalPixels; i++) {
          int idx = i * channels;
          unsigned char r = data[idx];
          unsigned char g = data[idx+1];
          unsigned char b = data[idx+2];
          add_or_update_color(&hist, uniqueCount, r, g, b);
     }
     return hist;
 }
 
 
 /* ===========================================================
    Quantization Algorithms (Placeholders)
    =========================================================== */
 
 /*
  * apply_popularity_quantization:
  *   Placeholder for the Popularity algorithm.
  *   Students should replace this implementation with their own.
  */
 unsigned char* apply_popularity_quantization(unsigned char* data, int width, int height, int channels, int targetColors) {
     // For now, simply return a copy of the original image.
     int totalPixels = width * height;
     unsigned char* newImg = malloc(totalPixels * channels);
     if (!newImg) {
          fprintf(stderr, "Memory allocation error in Popularity algorithm.\n");
          exit(1);
     }
     memcpy(newImg, data, totalPixels * channels);
     return newImg;
 }
 
 /*
  * apply_mediancut_quantization:
  *   Placeholder for the Median Cut algorithm.
  *   Students should replace this implementation with their own.
  */
 unsigned char* apply_mediancut_quantization(unsigned char* data, int width, int height, int channels, int targetColors) {
     // For now, simply return a copy of the original image.
     int totalPixels = width * height;
     unsigned char* newImg = malloc(totalPixels * channels);
     if (!newImg) {
          fprintf(stderr, "Memory allocation error in Median Cut algorithm.\n");
          exit(1);
     }
     memcpy(newImg, data, totalPixels * channels);
     return newImg;
 }
 
 
 /* ===========================================================
    Utility Functions
    =========================================================== */
 
 /*
  * save_image:
  *   Writes the image data to a file using stb_image_write.
  */
 void save_image(const char* filename, unsigned char* data, int width, int height, int channels) {
     if (!stbi_write_png(filename, width, height, channels, data, width * channels)) {
          fprintf(stderr, "Error writing image %s\n", filename);
          exit(1);
     }
     printf("Image saved: %s\n", filename);
 }
 