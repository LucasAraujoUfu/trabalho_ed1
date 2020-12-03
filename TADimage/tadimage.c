#include <stdio.h>
#include <stdlib.h>
#include "tadimage.h"

int readbin (char end[], matriz *Img)
{
    FILE *arg = fopen(end, "rb");
    if(arg == NULL)
        return INVALID_NULL_POINTER;
    else
    {
        int linha, coluna;
        fread(&linha, sizeof(int), 1, arg);
        fread(&coluna, sizeof(int), 1, arg);
        Img = allocMatriz (linha, coluna);

        if(Img == NULL)
            return OUT_NOT_MEMORY;
        else
        {
            int res;
            unsigned char let;
            fseek(arg, 8*sizeof(int), SEEK_SET);
            // pular o cabechalho
            for(int i=1; i < linhas(Img); i++)
            {
                for(int j=1; j < colunas(Img); j++)
                {
                    res = fread(&let, sizeof(unsigned char), 1, arg);
                    if(res == 1)
                        matrizsetvalue(Img, i, j, let);
                    else
                        return OUT_NOT_RANGE;
                }
            }
            
        }
    }
    fclose(arg);
    return SUCESS;
}


int cria_bin (char end[])
{
    FILE *arg = fopen("FILE.imm", "wb");
    if(arg == NULL)
        return ERRO_IMAGE_OPEN; //cod -6
    else
    {
        int linha=32, coluna=23;
        unsigned char let='*';
        fwrite(&linha, sizeof(int), 1, arg);
        fwrite(&coluna, sizeof(int), 1, arg);

        for (int i = 0; i < (linha*coluna); i++)
        {
            fwrite(&let, sizeof(unsigned char), 1, arg);
        }
        fclose(arg);
        return SUCESS;
    }
}