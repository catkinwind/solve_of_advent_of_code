#include <stdio.h>
#include <stdlib.h>

int pad[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

void left(int *i, int *j)
{
  if (*j > 0)
    (*j)--;
}

void right(int *i, int *j)
{
  if (*j< 2)
    (*j)++;
}

void up(int *i, int *j)
{
  if (*i >0)
    (*i)--;
}

void down(int *i, int *j)
{
  if (*i < 2)
    (*i)++;
}

int main(int argc, char *argv[])
{
  FILE  *f;
  char *line = NULL;
  size_t len;
  ssize_t cnt;
  char *ptr;
  int i = 1, j = 1;

  if (!(f = fopen("data", "r"))) {
    printf("error to open file\n");
  }

  while ((cnt = getline(&line, &len, f)) != -1) {
    if (cnt == 0)  continue;
    ptr = line;

    while(*ptr != '\0') {
      if (*ptr == 'L') left(&i, &j);
      else if (*ptr == 'R') right(&i, &j);
      else if (*ptr == 'U') up(&i, &j);
      else if (*ptr == 'D') down(&i, &j);
      ptr++;
    }
    printf("%d", pad[i][j]);
  }
  printf("\n");
  fclose(f);
}
