#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE  *f;
  int a, b, c;
  long cnt = 0;
  long num = 0;

  if (!(f = fopen("data", "r"))) {
    printf("error to open file\n");
  }

  while (fscanf(f, "%d%d%d", &a, &b, &c) != EOF) {
    if ((a > 0) && (b > 0) && (c > 0) &&
        (a + b > c) && (a + c > b) && (b + c > a))
      cnt++;
  }
  printf("valid: %d\n", cnt);
  fclose(f);
}
