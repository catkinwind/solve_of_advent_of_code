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
    if (e[pos]->count > e[pos-1]->count ||
        e[pos]->count == e[pos-1]->count &&
        e[pos]->c < e[pos-1]->c
       ) {
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

void decode(char *enc, int n)
{
  char *ptr = enc;
  int shift = n % 26;

  while(*ptr != '\0') {
    if (*ptr == '-') {
      *ptr = ' ';
      ptr++;
      continue;
    }
    *ptr = *ptr + shift;
    if (*ptr > 'z') {
      *ptr -= 26;
    }
    ptr++;
  }
  printf("%s: %d\n", enc, n);
}

int main(int argc, char *argv[])
{
  FILE  *f;
  char *line = NULL, *ptr, *plain;
  entry *e[27];
  int tail = 0;
  int state = 0; /* 0: chars, 1: numbers, 2: checksum */
  size_t len, word_len;
  ssize_t cnt;
  long sum = 0, n;
  int i;
  int match = 1;

  if (!(f = fopen("data", "r"))) {
    printf("error to open file\n");
  }

  while ((cnt = getline(&line, &len, f)) != -1) {
    ptr = line;
    match = 1;
    while(*ptr != 0) {
      if (*ptr == '-') {
        ptr++;
        continue;
      }
      switch(state) {
        case 0:
          if (*ptr >= 'a' && *ptr <= 'z') add_ch(e, &tail, *ptr);
          if (isdigit(*ptr)) {
            word_len = ptr - line;
            n = *ptr - '0';
            state = 1;
          }
          ptr++;
          break;
        case 1:
          if (isdigit(*ptr)) {
            n = n * 10 + (*ptr - '0');
          }
          if (*ptr == '[') {
            state = 2;
          }
          ptr++;
          break;
        case 2:
          if (tail < 5) {
            ptr +=5;
            break;
          }
          for (i = 0; i < 5; ++i) {
            if (e[i]->c != *ptr) {
              match = 0;
            }
            ptr++;
          }
          if (match) {
            sum += n;
            plain = (char *)malloc(word_len);
            strncpy(plain, line, word_len-1);
            plain[word_len - 1] = '\0';
            decode(plain, n);
          }
          state = 0;
          break;
      }
    }
    for (i = 0; i < tail; ++i) {
      free(e[i]);
      e[i] = NULL;
    }
    tail = 0;
  }
  printf("sum: %d\n", sum);
  fclose(f);
}
