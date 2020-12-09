#include <stdlib.h>

typedef struct matriz matriz;

int linhas(matriz *m);
int colunas(matriz *m);

void exitMaze(matriz* m);
void setexitMaze(matriz* m);
char* startMaze(matriz *m);

matriz* allocMatriz(int i, int j);
void freeMatriz(matriz* m);

int matrizSetValue(matriz *m,int i,int j,unsigned char n);
int matrizGetValue(matriz *m,int i,int j,unsigned char *n);

