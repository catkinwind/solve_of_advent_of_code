#include <stdio.h>
#include <stdlib.h>

char pad[7][7] = {
                 { '\0', '\0', '\0', '\0', '\0', '\0', '\0' },
                 { '\0', '\0', '\0', '1', '\0', '\0', '\0' },
                 { '\0', '\0', '2', '3', '4', '\0', '\0' },
                 { '\0', '5', '6', '7', '8', '9', '\0' },
                 { '\0', '\0', 'A', 'B', 'C', '\0', '\0' },
                 { '\0', '\0', '\0', 'D', '\0', '\0', '\0' },
                 { '\0', '\0', '\0', '\0', '\0', '\0', '\0' }
                };

void left(int *i, int *j)
{
  if (pad[*i][*j-1] != '\0')
    (*j)--;
}

void right(int *i, int *j)
{
  if (pad[*i][*j+1] != '\0')
    (*j)++;
}

void up(int *i, int *j)
{
  if (pad[*i-1][*j] != '\0')
    (*i)--;
}

void down(int *i, int *j)
{
  if (pad[*i+1][*j] != '\0')
    (*i)++;
}

int main(int argc, char *argv[])
{
  FILE  *f;
  char *line = NULL;
  size_t len;
  ssize_t cnt;
  char *ptr;
  int i = 3, j = 1;

  if (!(f = fopen("data2", "r"))) {
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
    printf("%c", pad[i][j]);
  }
  printf("\n");
  fclose(f);
}
