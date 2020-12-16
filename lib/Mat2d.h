#ifndef MAT2D
#define MAT2D
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

int size (matriz *m);
unsigned char pontos (matriz *m, int i, int j);

int preenche_image (matriz *img);
int dominio (matriz *m,int x,int y);

unsigned char **toArray(matriz *m);
matriz *arrayToMatriz(unsigned char **mt, int lin,int col);

#endif
