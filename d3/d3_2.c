#include <stdio.h>
#include <stdlib.h>

#define is_valid(a, b, c) (a) + (b) > (c) && \
  (a) + (c) > (b) && (b) + (c) > (a)

int main(int argc, char *argv[])
{
  FILE  *f;
  int arr[9];
  int *ptr = arr;
  long cnt = 0;

  if (!(f = fopen("data", "r"))) {
    printf("error to open file\n");
  }

  while (fscanf(f, "%d", ptr) != EOF) {
    if (ptr < arr + 8) {
      ptr++;
    } else {
      if (is_valid(arr[0], arr[3], arr[6])) cnt++;
      if (is_valid(arr[1], arr[4], arr[7])) cnt++;
      if (is_valid(arr[2], arr[5], arr[8])) cnt++;
      ptr = arr;
    }
  }
  printf("valid: %d\n", cnt);
  fclose(f);
}
