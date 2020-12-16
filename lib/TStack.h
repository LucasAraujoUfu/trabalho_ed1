#ifndef TSTACK
#define TSTACK
#include <stdlib.h>

typedef struct SPilha Pilha;

void pilha_init(Pilha* p);
char pilha_push(Pilha* p, int x, int y);
char pilha_pop(Pilha* p, int *x, int *y);

#endif