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

unsigned char pad[6][50] = {};

void lit(int a, int b)
{
  int i, j;
  for (i = 0; i < b; ++i) {
    for (j = 0; j < a; ++j)
      pad[i][j] = 1;
  }
}

void shift_row(int r, int x)
{
  int i = 0, tmp, j, cur;
  for(; i < x; i++) {
    cur = 50 - x + i;
    tmp = pad[r][cur];
    for (j = cur - 1; j >= i; j--) pad[r][j+1] = pad[r][j];
    pad[r][i] = tmp;
  }
}

void shift_column(int cl, int y)
{
  int i = 0, tmp, j, cur;
  for (; i < y; i++) {
    cur = 6 - y + i;
    tmp = pad[cur][cl];
    for (j = cur - 1; j >= i; j--) pad[j+1][cl] = pad[j][cl];
    pad[i][cl] = tmp;
  }
}

void parse(char *line) {
  char *del = " \n", *token, *str = line, *subtoken;
  char *saveptr, *saveptr2;
  int a, b;
  int mode = 0; /* 0: row 1: column */
  token = strtok_r(str, del, &saveptr);
  if (strcmp(token, "rect") == 0) {
    token = strtok_r(NULL, del, &saveptr);
    printf("%s\n", token);
    subtoken = strtok_r(token, "x", &saveptr2);
    a = atoi(subtoken);
    subtoken = strtok_r(NULL, "x", &saveptr2);
    b = atoi(subtoken);
    lit(a, b);
  } else {
    token = strtok_r(NULL, del, &saveptr);
    if (strcmp(token, "row") == 0) {
      mode = 0;
    } else {
      mode = 1;
    }
    token = strtok_r(NULL, del, &saveptr);
    a = atoi(token+2);
    token = strtok_r(NULL, del, &saveptr);
    token = strtok_r(NULL, del, &saveptr);
    b = atoi(token);
    if (!mode) {
      shift_row(a, b);
    } else {
      shift_column(a, b);
    }
  }
}

int main(int argc, char *argv[])
{
  FILE  *f;
  char *line = NULL;
  size_t len;
  ssize_t cnt;
  int i, j, count = 0;

  if (!(f = fopen("data", "r"))) {
    printf("error to open file\n");
  }

  while ((cnt = getline(&line, &len, f)) != -1) {
    parse(line);
  }

  for (i = 0; i < 6; i++) {
    for (j = 0; j < 50; j++) {
      printf("%d", pad[i][j]);
      count += pad[i][j];
    }
    printf("\n");
  }

  printf("Result: %d\n", count);

  free(line);
  fclose(f);
}
