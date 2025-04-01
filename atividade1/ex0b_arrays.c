#include <stdio.h>
#include <stdlib.h>

int main() {
  unsigned char arrEstatico[10];
  unsigned char *arrDinamico = malloc(10);

  for (int i = 0; i < 10; i++) {
    arrDinamico[i] = i;
    arrEstatico[i] = i;
  }

  for (int i = 0; i < 10; i++) {
    printf("%d ", arrEstatico[i]);
  }

  printf("\n");

  for (int i = 0; i < 10; i++) {
    printf("%d ", arrDinamico[i]);
  }

  free(arrDinamico);
  return 0;
}