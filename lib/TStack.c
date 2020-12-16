#include <stdio.h>
#include "TStack.h"

struct SData
{
  int x, y;
  struct SData* next;
};
typedef struct SData Data;

struct SPilha
{
  Data* data;
};


void pilha_init(Pilha* p)
{
  p->data = NULL;
}

char pilha_push(Pilha* p, int x, int y)
{
  Data* d = malloc(sizeof(Data));
  if (d == NULL) return 0;

  d->x = x;
  d->y = y;
  d->next = p->data;
  p->data = d;
  return 1;
}

char pilha_pop(Pilha* p, int *x, int *y)
{
  if (p->data == NULL) return 0;
  *x = p->data->x;
  *y = p->data->y;
  Data* d = p->data->next;
  free(p->data);
  p->data = d;
  return 1;
}