#include "sort.h"
#include "color.h"

// https://www.geeksforgeeks.org/comparator-function-of-qsort-in-c/

int compareByCount(const void *a, const void *b) {
  Color *colorA = (Color *)a;
  Color *colorB = (Color *)b;

  return colorB->count - colorA->count;
}

int compareByR(const void *a, const void *b) {
  Color *colorA = (Color *)a;
  Color *colorB = (Color *)b;

  return colorB->r - colorA->r;
}

int compareByG(const void *a, const void *b) {
  Color *colorA = (Color *)a;
  Color *colorB = (Color *)b;

  return colorB->g - colorA->g;
}

int compareByB(const void *a, const void *b) {
  Color *colorA = (Color *)a;
  Color *colorB = (Color *)b;

  return colorB->b - colorA->b;
}