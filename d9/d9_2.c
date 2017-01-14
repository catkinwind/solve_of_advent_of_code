#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

/*
 * parse a and b. if the structure is incorrect, return 0;
 */
int
get_ab(char *beg, char *end, int *a, int *b) {
  *a = 0, *b = 0;
  while (beg < end && *beg != 'x') {
    if (!isdigit(*beg)) {
      printf("%c\n", *beg);
      return 0;
    }
    *a = *a * 10 + *beg - '0';
    beg++;
  }
  if (beg == end) return 0;

  beg++;
  while (beg <= end) {
    if (!isdigit(*beg)) {
      printf("%c\n", *beg);
      return 0;
    }
    *b = *b * 10 + *beg - '0';
    beg++;
  }
  return 1;
}

long long analyze(char *line, char *end)
{
  char *beg = NULL;
  long long count = 0;
  int instr = 0;
  int a, b;

  while (line <= end) {
    if (*line == '(') {
      if (instr) {
        count += line - beg + 1;
      }
      beg = line + 1;
      instr = 1;
    } else if (instr && *line == ')') {
      if (get_ab(beg, line - 1, &a, &b)) {
        count += analyze(line+1, line + a) * b;
        line += a;
      } else {
        count += line - beg + 2; // current ) is also an available
      }
      instr = 0;
    } else if (!instr) {
      count++;
    }
    line++;
    if (count > pow(2, 32) - 1 ) {
      printf("%d\n", count);
    }
  }
  return count;
}

int main(int argc, char *argv[])
{
  FILE  *f;
  char *line = NULL, *ptr1, *ptr2;
  size_t len;
  ssize_t cnt;
  long long count = 0;

  if (!(f = fopen("data", "r"))) {
    printf("error to open file\n");
  }

  cnt = getline(&line, &len, f);
  if (line[cnt-1] == '\n') {
    cnt--;
  }
  count += analyze(line, line + cnt - 1);

  printf("Result: %lld\n", count);

  free(line);
  fclose(f);
}
