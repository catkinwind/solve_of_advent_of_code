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

void walk(Point *pos, Direction dir, unsigned int step)
{
  switch(dir) {
    case NOR:
      pos->y += step;
      break;
    case EAST:
      pos->x += step;
      break;
    case SOU:
      pos->y -= step;
      break;
    case WEST:
      pos->x -= step;
      break;
  }
}

#define MAXSTR 1024;

int main(int argc, char *argv[])
{
  Point p = { 0, 0 };
  char *steps = NULL;
  size_t len;
  char *d;
  Direction dir = NOR;
  unsigned int step = 0;
  
  printf("Please input the steps:\n> ");
  getline(&steps, &len, stdin);
  printf("%s\n", steps);
  d = steps;
  while (*d != '\0') {
    if (*d == 'R') dir = turn_right(dir);
    else if (*d == 'L') dir = turn_left(dir);
    else if (isdigit(*d)) step = step * 10 + (*d - '0');
    else {
      walk(&p, dir, step);
      step = 0;
    }
    d++;
  }
  if (step > 0) {
    walk(&p, dir, step);
  }
  printf("Result: %d", abs(p.x) + abs(p.y));
  free(steps);
  
  return 0;
}
