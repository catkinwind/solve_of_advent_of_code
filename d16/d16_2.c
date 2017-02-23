#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define SIZE 35651584

size_t calc_size(int n)
{
  while(n < SIZE)
    n = n * 2 + 1;
}

void checksum(char *checksum)
{
  int i, l = SIZE;

  while (l % 2 == 0) {
    for (i = 0; i < l; i += 2) {
      checksum[i/2] = checksum[i] == checksum[i+1] ? '1' : '0';
    }
    l = l / 2;
  }
  checksum[l] = 0;
}

void write_bytes(char *disk, size_t cur)
{
  disk[cur] = '0';
  int i, j;
  for (i = 0; i < cur; i++) {
    j = cur * 2 - i;
    disk[j] = disk[i] == '0' ? '1' : '0';
  }
  disk[cur * 2 + 1] = 0;
}

int main(int argc, char *argv[])
{
  char *seed = "10011111011011001";
  time_t t1, t2;
  t1 = clock();

  size_t cur = strlen(seed), max = calc_size(cur);
  char *disk = (char *)malloc(max);
  strcpy(disk, seed);
  printf("max: %d\n%s\n", max, disk);

  while (cur < SIZE) {
    write_bytes(disk, cur);
    cur = cur * 2 + 1;
  }
  checksum(disk);
  t2 = clock();
  printf("Time spent: %.3f\n", (t2 * 1.0 - t1) / CLOCKS_PER_SEC);
  printf("Result: %s\n", disk);
}
