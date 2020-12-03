#include <stdio.h>
#include <stdlib.h>
#include "./matriz/TADmatriz.h"


int main (void)
{
    unsigned char let;
    int res;
    matriz *mtz = allocMatriz (32, 32);
    for (int i = 0; i < linhas(mtz); i++)
    {
        for (int j = 0; j < colunas(mtz); j++)
        {
            let = rand() % 255;
            matrizsetvalue(mtz, i, j, let);
        }
    }

    print_matriz(mtz);
    freeMatriz(mtz);
    return 0;
}