#include <stdio.h>

int main() {
  FILE *f = fopen("ascii.txt", "w");
  for (int i = 1; i < 127; i++) {
    fprintf(f, "%c\n", i);
  }
  fclose(f);
  return 0;
}