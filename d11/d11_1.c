#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ENTRY_SIZE 10

typedef struct _state {
  int e;
  int *c;
} state;

typedef struct _pair {
  void *entry;
  int  *value;
} pair;

typedef struct _node {
  void *ptr;
  struct _node *next;
} node;

/*
 * allocate space for state, and set values.
 */
state *create_state(int e, int *c)
{
  state *tmp;
  tmp = (state *)malloc(sizeof(state));
  tmp->e = e;
  tmp->c = c;
  return tmp;
}

void free_state(state *s)
{
  free(s);
}

node *create_node(state *s)
{
  node *tmp = (node *)malloc(sizeof(node));
  tmp->next = NULL;
  tmp->ptr = s;
  return tmp;
}

node *init()
{
  state *s = (state *)malloc(sizeof(state));
  s->e = 0;
  s->c = (int *)malloc(ENTRY_SIZE * sizeof(int));
  s->c[0] = 1;
  s->c[1] = 3;
  s->c[2] = 3;
  s->c[3] = 3;
  s->c[4] = 3;
  s->c[5] = 2;
  s->c[6] = 2;
  s->c[7] = 2;
  s->c[8] = 2;
  s->c[9] = 1;
  node *n = create_node(s);
  return n;
}

node *lookup_node(node *list, int *c, int e)
{
  int matched = 0;
  state *tmp;
  int i;
  while (list) {
    tmp = (state *)*list->ptr;
    matched = *tmp->e == e;
    for (i = 0; i < ENTRY_SIZE; ++i) {
      matched = matched && (c[i] == tmp->c[i]);
    }
    if (matched) {
      return list;
    }
    list = list->next;
  }
  return null;
}

node *popup(node **stack)
{
  node *tmp = *stack;
  if (tmp ) {
    *stack = *statck->next;
  }
  return tmp;
}

int is_goal(state *st)
{
  if (st->e != 4) return 0;
  int i = 0;
  for (; i < ENTRY_SIZE; ++i) {
    if (st->c[i] != 4) return 0;
  }
  return 1;
}

int is_valid(int c[], int e)
{
  int h = ENTRY_SIZE / 2, i, has_g = 0;
  for (i = h; i < ENTRY_SIZE; ++I) {
    if (c[i] == e) {
      has_g = 1;
      break;
    }
  }
  if (!has_g) return 1;

  for (i = 0; i < h; ++i) {
    if (c[i] == e && c[ENTRY_SIZE-i-1] != e) {
      return 0;
    }
  }
  return 1;
}

int *try_down(state *st, int f_a, int f_b)
{
  int e = tmp->e, *n = NULL;
  st->c[f_a]--;
  if (f_b != -1) {
    st->c[f_b]--;
  }

  if (is_valid(st->c, e) && is_valid(st->c, e-1)) {
    n = (int *)malloc(ENTRY_SIZE * sizeof(int));
  }
  st->c[f_a]++;
  if (f_b != -1) {
    st->c[f_b]++;
  }
  return n;
}

void astar() {
  node *closed, *open, *g, *tmp, nei;
  state *st;
  int i, j, *arr;

  open = init();
  g = (node *)malloc(sizeof(node));
  g->entry = open->ptr;
  g->value = 0;

  while (tmp = popup(&open)) {
    st = (state *)tmp->ptr;
    // add to closed;
    tmp->next = closed;
    closed = tmp;

    if (is_goal(st)) {
      break;
    }
    // first try going down;
    if (tmp->e > 0) {
      for(i = 0; i< ENTRY_SIZE; ++i) {
        if (tmp->c[i] == tmp->e) {
          arr = try_down(tmp, i)
          if (arr && !lookup_node(closed, arr, e-1))
            if (nei = lookup_node(open, arr, e-1)) {
              
            }
          } else {
            free(arr);
            arr = NULL;
          }
        }

      }

    }
    // try going up;

  }

}



#define fill0(f, beg) \
  for (i = 0; i < 10; i++) f[i] = 0;

void init()
{
  f[0][0] = 1, f[0][9] = 1;
  f[1][5] = 1, f[1][6] = 1, f[1][7] = 1, f[1][8] = 1;
  f[2][1] = 1, f[2][2] = 1, f[2][3] = 1, f[2][4] = 1;
}

int is_empty(int n)
{
  int i;
  if (n < 0 || n > 3) return 1;
  for (i = 0; i < 10; i++) {
    if (f[n][i] == 1) return 0;
  }
  return 1;
}

int is_full(int n) {
  int i;
  for (i = 0; i < 10; i++) {
    if (f[n][i] == 0) return 0;
  }
  return 1;
}


/*
 * Everytime we go up, taking 2.
 */
void go_up(int src)
{
  int i = 0, a = -1, b = -1;
  int sum = 0;

  // First Choose a matched pair to go up.
  for (i = 0; i <=4; i++) {
    sum += f[src][i];
    if (f[src][i] == 1 && f[src][9-i] == 1) {
      a = i, b = 9 - i;
      break;
    }
  }
  // There are only managers.
  if (a == -1 && sum) {
    for (i = 0; i <= 4; i++) {
      if (f[src][i] ==  1 && a == -1) {
        a = i;
        continue;
      }
      if (f[src][i] == 1 && b == -1) {
        b = i;
        break;
      }
    }
  } else if(a == -1) {
    for (i = 5; i <= 9; i++) {
      if (f[src][i] ==  1 && a == -1) {
        a = i;
        continue;
      }
      if (f[src][i] == 1 && b == -1) {
        b = i;
        break;
      }
    }
  }
  if (a == -1 || b == -1) {
    printf("error: a - %d, b - %d, src - %d\n", a, b, src);
    exit(1);
  }
  f[src][a] = 0, f[src][b] = 0;
  f[src+1][a] = 1, f[src+1][b] = 1;
}

void go_down(int src) {
  int i, a = -1;;
  for (i = 0; i <=4; i++) {
    if (f[src][i] == 1 && f[src][9-i] == 0) {
      a = i;
      break;
    }
  }
  if (a == -1) {
    for (i = 0; i <=4; i++) {
      if (f[src][i] == 1) {
        a = i;
        break;
      }
    }
  }
  f[src][a] = 0;
  f[src-1][a] = 1;
}

void run() {
  int cnt = 0, src = 0;

  while(1) {
    if (src == 3 && is_full(src)) {
      printf("result: %d\n", cnt);
      return;
    }

    if (is_empty(src - 1)) {
      go_up(src);
      src++;
      cnt++;
    } else {
      go_down(src);
      src--;
      cnt++;
    }
  }
}

int main(int argc, char *argv[])
{
  init();
  run();
}
