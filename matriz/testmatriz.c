#include <stdio.h>
#include <stdlib.h>
#include "TADmatriz.h"

void preenche_aleatorio (void);
// aquivo feito para testar possiveis erros no matriz;


int main (void)
{
    preenche_aleatorio();
    return 0;
}

void preenche_aleatorio (void)
{
    matriz *Mtz = allocMatriz(32,23);
    unsigned char let;

    for (int i = 0; i < linhas(Mtz); i++)
    {
        for (int j = 0; j < colunas(Mtz); j++)
        {
            let = rand() % 255;
            matrizsetvalue (Mtz, i, j, let);
        }
        
    }
    print_matriz(Mtz);
    freeMatriz(Mtz);
    return;
}