#ifndef TADMATRIZ_H
#define TADMATRIZ_H

#define SUCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_NOT_RANGE -2
#define OUT_NOT_MEMORY -3
#define INVALID_OPERATION -4
#define INVALID_INPUT -5

typedef struct TADmatriz matriz;

int colunas (matriz *mtz);

int linhas (matriz *mtz);

int matrizgetvalue (matriz *mtz, int linha, int coluna, unsigned char *let);

int matrizsetvalue (matriz *mtz, int linha, int coluna, unsigned char let);

int print_matriz (matriz *mtz);

matriz* allocMatriz (int i, int j);

void freeMatriz(matriz *mtz);


#endif