#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int has_abba(char *begin, char *end) {
  char *p;
  for (p = begin + 1; p < end - 1; p++) {
    if (*p == *(p+1) && *p != *(p-1) && *(p-1) == *(p+2))
      return 1;
    if (*p == *(p+1))
      p++;
  }
  return 0;
}

int main(int argc, char *argv[])
{
  FILE  *f;
  char *line = NULL, *ptr1, *ptr2;
  size_t len;
  ssize_t cnt;
  int state = 0; /* 0: outer, 1: inner */
  int count = 0, outer = 0, inner = 0;

  if (!(f = fopen("data", "r"))) {
    printf("error to open file\n");
  }

  while ((cnt = getline(&line, &len, f)) != -1) {
    ptr1 = line, ptr2 = line;
    state = 0;
    outer = 0, inner = 0;
    while(*ptr2 != '\0') {
      if (*ptr2 == '[') {
        outer = outer || has_abba(ptr1, ptr2 - 1);
        state = 1;
        ptr1 = ptr2 + 1;
      } else if (*ptr2 == ']') {
        inner = has_abba(ptr1, ptr2 - 1);
        if (inner) break;
        state = 0;
        ptr1 = ptr2 + 1;
      }
      ptr2++;
    }
    if (!inner && ptr2 > ptr1 + 3) {
      if (!state) {
        outer = outer || has_abba(ptr1, ptr2 - 1);
      } else {
        inner = inner || has_abba(ptr1, ptr2 - 1);
      }
    }
    if (outer && !inner) {
      count++;
    }
    ptr1 = NULL,  ptr2 = NULL;
  }

  printf("Result: %d\n", count);

  free(line);
  fclose(f);
}
