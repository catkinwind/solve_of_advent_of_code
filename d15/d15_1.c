#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct _disc{
  int current;
  int number;
} Disc;

Disc *create_disc(int current, int number)
{
  Disc *n = (Disc *)malloc(sizeof(Disc));
  n->current = current;
  n->number = number;
}

void free_disc(Disc *n)
{
  if (n != NULL) {
    free(n);
  }
}

void init(Disc **discs) {
  discs[0] = NULL;
  discs[1] = create_disc(11, 13);
  discs[2] = create_disc(0, 5);
  discs[3] = create_disc(11, 17);
  discs[4] = create_disc(0, 3);
  discs[5] = create_disc(2, 7);
  discs[6] = create_disc(17, 19);
}

void clean(Disc **discs) {
  int i = 0;
  for (; i < 7; i++) {
    free_disc(discs[i]);
    discs[i] = NULL;
  }
}

int main(int argc, char *argv[])
{
  Disc *discs[7];
  int i = 0;
  time_t t1 = clock(), t2;

  init(discs);

  while(1) {
    int l, passed = 1;
    for (l = 1; l < 7; ++l) {
      if ((i + discs[l]->current + l) % discs[l]->number != 0) {
        passed = 0;
        break;
      }
    }
    if (passed) {
      printf("Result: %d\n", i);
      break;
    }
    i++;
  }

  clean(discs);

  t2 = clock();
  printf("Time spent: %.3f\n", (float)(t2 - t1) / CLOCKS_PER_SEC);
}
