#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef enum Direction{ NOR, EAST, SOU, WEST } Direction;

typedef struct Point{
  int x;
  int y;
} Point;

Direction turn_left(Direction dir)
{
  if (dir == NOR) return WEST;
  return dir - 1;
}

Direction turn_right(Direction dir)
{
  if (dir == WEST)  return NOR;
  return dir + 1;
}

typedef struct Seg {
  Point *p1;
  Point *p2;
  struct Seg *next;
  struct Seg *prev;
} Segment;

#define MAXSTR 1024;

typedef struct List {
  Segment *head;
  Segment *tail;
} List;

void init_list(List *list)
{
  list->head = (Segment *)malloc(sizeof(Segment));
  list->tail = (Segment *)malloc(sizeof(Segment));
  list->head->next = list->tail;
  list->tail->prev = list->head;
}

void destroy_list(List *list)
{
  free(list->head);
  free(list->tail);
}

typedef int (*compare)(Segment *s1, Segment *s2);

void insert(List *list, Segment *s, compare cmp) {
  Segment *head = list->head;
  Segment *tail = list->tail;
  Segment *next = head->next;
  while(next != tail && !cmp(s, next))  next = next->next;
  next->prev->next = s;
  s->prev = next->prev;
  s->next = next;
  next->prev = s;
}

int comparex(Segment *s1, Segment *s2)
{
  return s1->p1->x - s2->p1->x;
}

int comparey(Segment *s1, Segment *s2)
{
  return s1->p1->y - s2->p1->y;
}

int walk_to_east(List *list, Point *p, Point *src)
{
  Segment *cur = list->head->next;
  while(cur != list->tail) {
    if (cur->p1->x == p->x && cur->p2 != src && (
        p->y >= cur->p1->y && p->y <= cur->p2->y ||
        p->y >= cur->p2->y && p->y <= cur->p1->y)) {
      return 1;
    }
    cur = cur->next;
  }
  return 0;
}

int walk_to_west(List *list, Point *p, Point *src)
{
  Segment *cur = list->tail->prev;
  while(cur != list->head) {
    if (cur->p1->x == p->x && cur->p2 != src && (
        p->y >= cur->p1->y && p->y <= cur->p2->y ||
        p->y >= cur->p2->y && p->y <= cur->p1->y)) {
      return 1;
    }
    cur = cur->prev;
  }
  return 0;
}

int walk_to_nor(List *list, Point *p, Point *src)
{
  Segment *cur = list->head->next;
  while(cur != list->tail) {
    if (cur->p1->y == p->y && cur->p2 != src && (
        p->x >= cur->p1->x && p->x <= cur->p2->x ||
        p->x >= cur->p2->x && p->x <= cur->p1->x)) {
      return 1;
    }
    cur = cur->next;
  }
  return 0;
}

int walk_to_sou(List *list, Point *p, Point *src)
{
  Segment *cur = list->tail->prev;
  while(cur != list->head) {
    if (cur->p1->y == p->y && cur->p2 != src && (
        p->x >= cur->p1->x && p->x <= cur->p2->x ||
        p->x >= cur->p2->x && p->x <= cur->p1->x)) {
      return 1;
    }
    cur = cur->prev;
  }
  return 0;
}

int walk(Point *src, Direction dir, unsigned int step,
            List *listx, List *listy, Point *dst)
{
  Segment *seg;
  int i = 1;
  switch(dir) {
    case NOR:
      // TODO
      dst->y = src->y;
      dst->x = src->x;
      for(i = 1; i <= step; i++) {
        (dst->y)++;
        if (walk_to_nor(listy, dst, src)) {
          return 1;
        }
      }
      seg = (Segment *)malloc(sizeof(Segment));
      seg->p1 = src;
      seg->p2 = dst;
      insert(listx, seg, comparex);
      break;
    case EAST:
      dst->x = src->x;
      dst->y = src->y;
      for (i = 1; i <= step; i++) {
        (dst->x)++;
        if (walk_to_east(listx, dst, src)) return 1;
      }
      seg = (Segment *)malloc(sizeof(Segment));
      seg->p1 = src;
      seg->p2 = dst;
      insert(listy, seg, comparey);
      break;
    case SOU:
      dst->y = src->y;
      dst->x = src->x;
      for(i = 1; i <= step; i++) {
        (dst->y)--;
        if (walk_to_sou(listy, dst, src)) return 1;
      }
      seg = (Segment *)malloc(sizeof(Segment));
      seg->p1 = src;
      seg->p2 = dst;
      insert(listx, seg, comparex);
      break;
    case WEST:
      dst->x = src->x;
      dst->y = src->y;
      for (i = 1; i <= step; i++) {
        (dst->x)--;
        if (walk_to_west(listx, dst, src)) return 1;
      }
      seg = (Segment *)malloc(sizeof(Segment));
      seg->p1 = src;
      seg->p2 = dst;
      insert(listy, seg, comparey);
      break;
  }
  return 0;
}

void release_list_entry(List *list)
{
  Segment *cur;
  cur = list->head->next;
  Segment *tmp;
  while (cur != list->tail) {
    tmp = cur->next;
    free(cur);
    cur = tmp;
  }
}

Point *create_point(Point *p[], int tail)
{
  Point *tmp = (Point *)malloc(sizeof(Point));
  p[tail++] = tmp;
  return tmp;
}

int main(int argc, char *argv[])
{
  Point *src, *dst;
  Point *p[1024];
  int tail = 0;
  char *steps = NULL;
  size_t len;
  char *d;
  Direction dir = NOR;
  unsigned int step = 0;
  List xlist, ylist;
  int got = 0;

  init_list(&xlist);
  init_list(&ylist);

  printf("Please input the steps:\n> ");
  getline(&steps, &len, stdin);
  printf("%s\n", steps);
  d = steps;
  src = create_point(p, tail);
  src->x = 0;
  src->x = 0;
  while (*d != '\0') {
    if (*d == 'R') dir = turn_right(dir);
    else if (*d == 'L') dir = turn_left(dir);
    else if (isdigit(*d)) step = step * 10 + (*d - '0');
    else if (*d == ',') {
      dst = create_point(p, tail);
      if (got = walk(src, dir, step, &xlist, &ylist, dst)) {
        break;
      }
      src = dst;
      step = 0;
    }
    d++;
  }
  if (!got && step > 0) {
    dst = create_point(p, tail);
    got = walk(src, dir, step, &xlist, &ylist, dst);
  }
  if (got)
    printf("Result: %d\n", abs(dst->x) + abs(dst->y));
  int i;
  for (i = 0; i < tail; i++) {
    free(p[i]);
  }
  release_list_entry(&xlist);
  release_list_entry(&ylist);
  destroy_list(&xlist);
  destroy_list(&ylist);

  free(steps);

  return 0;
}
