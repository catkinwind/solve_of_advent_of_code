#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXITEM 128

typedef struct entry{
  char a;
  char b;
} entry;

entry *find(entry *e[], const int tail, char a, char b)
{
  int i;
  for (i = 0; i < tail; ++i) {
    if (e[i]->a == a && e[i]->b == b) {
      return e[i];
    }
  }

  return NULL;
}

void add_entry(entry *e[], int *tail, char a, char b)
{
  if (find(e, *tail, a, b)) return;
  entry *tmp = (entry *)malloc(sizeof(entry));
  tmp->a = a;
  tmp->b = b;
  if (*tail >= MAXITEM) {
    printf("Full\n");
  }
  e[*tail] = tmp;
  *tail += 1;
}

int has_aba(char *begin, char *end, entry *outer[], int *ot,
            entry * inner[], int it) {
  char *p;
  char a, b;
  for (p = begin + 1; p < end; p++) {
    if (*p != *(p+1) && *(p-1) == *(p+1)) {
      a = *(p-1), b = *p;
      if (find(inner, it, a, b)) {
        return 1;
      }
      add_entry(outer, ot, a, b);
    }
  }
  return 0;
}

int has_bab(char *begin, char *end, entry *outer[], int ot,
            entry * inner[], int *it) {
  char *p;
  char a, b;
  for (p = begin + 1; p < end; p++) {
    if (*p != *(p+1) && *(p-1) == *(p+1)) {
      a = *p, b = *(p-1);
      if (find(outer, ot, a, b)) {
        return 1;
      }
      add_entry(inner, it, a, b);
    }
  }
  return 0;
}

void destroy(entry *e[], int *tail) {
  int i;
  for (i = 0; i < *tail; i++) {
    free(e[i]);
    e[i] = NULL;
  }
  *tail = 0;
}


int main(int argc, char *argv[])
{
  FILE  *f;
  char *line = NULL, *ptr1, *ptr2;
  size_t len;
  ssize_t cnt;
  entry *outer[MAXITEM], *inner[MAXITEM];
  int ot = 0, it = 0;
  int state = 0; /* 0: outer, 1: inner */
  int count = 0, matched = 0;

  if (!(f = fopen("data", "r"))) {
    printf("error to open file\n");
  }

  while ((cnt = getline(&line, &len, f)) != -1) {
    ptr1 = line, ptr2 = line;
    state = 0;
    matched = 0;
    while(*ptr2 != '\0' && *ptr2 != '\n') {
      if (*ptr2 == '[') {
        matched = has_aba(ptr1, ptr2 - 1, outer, &ot, inner, it);
        if (matched) break;
        state = 1;
        ptr1 = ptr2 + 1;
      } else if (*ptr2 == ']') {
        matched = has_bab(ptr1, ptr2 - 1, outer, ot, inner, &it);
        if (matched) break;
        state = 0;
        ptr1 = ptr2 + 1;
      }
      ptr2++;
    }
    if (!matched && ptr2 > ptr1 + 3) {
      if (!state) {
        matched = has_aba(ptr1, ptr2 - 1, outer, &ot, inner, it);
      } else {
        matched = has_bab(ptr1, ptr2 - 1, outer, ot, inner, &it);
      }
    }
    if (matched){
      count++;
    }
    ptr1 = NULL,  ptr2 = NULL;
    destroy(outer, &ot);
    destroy(inner, &it);
  }

  printf("Result: %d\n", count);

  free(line);
  fclose(f);
}
