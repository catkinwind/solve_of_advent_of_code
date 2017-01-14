#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct entry{
  int count;
  char c;
} entry;

void swap(entry *e[], int i, int j)
{
  entry *tmp = e[i];
  e[i] = e[j];
  e[j] = tmp;
}

void reorg(entry *e[], int pos)
{
  if (pos == 0) {
    return;
  }
  for (pos; pos > 0; pos--) {
    if (e[pos]->count > e[pos-1]->count) {
      swap(e, pos, pos - 1);
    }
  }
}

void add_ch(entry *e[], int *tail, char c)
{
  int i = 0;
  for (i = 0; i < *tail; ++i) {
    if (e[i]->c == c) {
      (e[i]->count)++;
      reorg(e, i);
      return;
    }
  }
  entry *tmp = (entry *)malloc(sizeof(entry));
  tmp->c = c;
  tmp->count = 1;
  e[*tail] = tmp;
  *tail += 1;
  reorg(e, *tail - 1);
}

int main(int argc, char *argv[])
{
  FILE  *f;
  char *line = NULL, *ptr, *plain;
  entry *e[8][27];
  int tail[8] = {0};
  size_t len;
  ssize_t cnt;
  char res[9];
  int i;

  if (!(f = fopen("data", "r"))) {
    printf("error to open file\n");
  }

  while ((cnt = getline(&line, &len, f)) != -1) {
    for (i = 0; i < 8; i++) {
      add_ch(e[i], tail + i, line[i]);
    }
  }

  for (i = 0; i < 8; i++) {
    printf("%c", e[i][tail[i]-1]->c);
  }
  printf("\n");

  free(line);
  fclose(f);
}
