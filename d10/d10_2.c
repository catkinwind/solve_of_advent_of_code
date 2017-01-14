#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct _bot{
  int card1;
  int card2;
  int low;
  int high;
} Bot;

Bot *bots[300] = {};
int bot_max = -1;
int out0 = 1, out1 = 1, out2 = 1;

#define next_i_token(cnt) for (i = 0; i < cnt; i++) {\
  token = strtok_r(str, delm, &saveptr);\
}

int full(int);
Bot *create_bot(int b);
void give_out(int b);

void  give_to_bot(int b, int c) {
  if (bots[b] == NULL) create_bot(b);
  if (full(b)) {
    give_out(b);
    return;
  }
  if (bots[b]->card1 == -1) {
    bots[b]->card1 = c;
    return;
  }
  bots[b]->card2 = c;
}

Bot *create_bot(int b) {
  Bot *tmp = (Bot *)malloc(sizeof(Bot));
  if (bots[b] != NULL) {
    printf("fault\n");
  }
  tmp->card1 = -1;
  tmp->card2 = -1;
  bots[b] = tmp;
  if (b > bot_max) bot_max = b;
  return tmp;
}

void parse(char *line) {
  char *str = line, *saveptr, *delm = " \n";
  char *token;
  int i, b, l, h, v, factor;
  next_i_token(1);
  str = NULL;
  if (strcmp(token, "bot") == 0) {
    next_i_token(1);
    b = atoi(token);
    next_i_token(4);
    factor = strcmp(token, "bot") == 0? 1 : -1;
    next_i_token(1);
    l = atoi(token);
    if (factor < 0) l = -1 * l -1;
    next_i_token(4);
    factor = strcmp(token, "bot") == 0? 1 : -1;
    next_i_token(1);
    h = atoi(token);
    if (factor < 0) h = -1 *h - 1;

    if (bots[b] == NULL) {
      create_bot(b);
    }
    bots[b]->low = l;
    bots[b]->high = h;
    return;
  }
  next_i_token(1);
  v = atoi(token);
  next_i_token(4);
  b = atoi(token);
  if (bots[b] == NULL) {
    create_bot(b);
  }
  give_to_bot(b, v);
}

void give_to(int dest, int v)
{
  if (dest >= 0) {
    give_to_bot(dest, v);
  } else if (dest == -1) {
    out0 *= v;
  } else if (dest == -2) {
    out1 *= v;
  } else if (dest == -3) {
    out2 *= v;
  }
}

void give_out(int b)
{
  int h = bots[b]->card1 > bots[b]->card2 ?
          bots[b]->card1 : bots[b]->card2,
    l = bots[b]->card1 > bots[b]->card2 ?
        bots[b]->card2 : bots[b]->card1;
  give_to(bots[b]->high, h);
  give_to(bots[b]->low, l);
  bots[b]->card1 = -1;
  bots[b]->card2 = -1;
}

int full(int b)
{
  return bots[b] && bots[b]->card1 > -1 && bots[b]->card2 > -1;
}

int match(int b, int x, int y)
{
  return bots[b]->card1 == x && bots[b]->card2 == y ||
    bots[b]->card1 == y && bots[b]->card2 == x;
}

void run()
{
  int i = 0;
  int ran = 0;
  while(1) {
    ran = 0;
    for (i = 0; i <= bot_max; i++) {
      if (!full(i)) continue;
      give_out(i);
      ran = 1;
    }
    if (!ran) return;
  }
}

void free_bots()
{
  int i;
  for (i = 0; i < bot_max; i++)
  {
    if (bots[i] != NULL) free(bots[i]);
  }
}

int main(int argc, char *argv[])
{
  FILE  *f;
  char *line = NULL, *ptr1, *ptr2;
  size_t len;
  ssize_t cnt;

  if (!(f = fopen("data", "r"))) {
    printf("error to open file\n");
  }

  while ((cnt = getline(&line, &len, f)) != -1) {
    parse(line);
  }

  run();
  printf("Result: %d %d %d %d\n", out0, out1, out2, out0 * out1 * out2);
  free_bots();

  free(line);
  fclose(f);
}
