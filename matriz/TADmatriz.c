#include <stdio.h>
#include <stdlib.h>
#include "TADmatriz.h"

struct TADmatriz
{
    int nrows;
    int ncols;
    unsigned char *data;
};

matriz* allocMatriz (int i, int j)
{
    if(i > 0 && j > 0)
    {
        matriz *mtz = (matriz*) malloc (sizeof(matriz));
        if(mtz != NULL)
        {
            mtz->data = (unsigned char*) malloc (i*j*sizeof(unsigned char));
            if(mtz->data != NULL)
            {
                mtz->nrows = i;
                mtz->ncols = j;
                return mtz;
            }
            else
                free(mtz);
        }
    }
    return NULL;
}

int print_matriz (matriz *mtz)
{
    if(mtz != NULL && mtz->data != NULL)
    {
        for (int col = 0; col < mtz->ncols; col++)
        {
            for (int lin = 0; lin < mtz->nrows; lin++)
            {
                printf("%3d ",mtz->data[(col*mtz->nrows)+lin]);
            }
            printf("\n");
        }
        return SUCESS;
    }
    return INVALID_NULL_POINTER;
}

int matrizsetvalue (matriz *mtz, int linha, int coluna, unsigned char let)
{
    if(mtz == NULL || mtz->data == NULL)
        return INVALID_NULL_POINTER;
    else if(linha < 0 || coluna < 0)
        return OUT_NOT_RANGE;
    else
    {
        mtz->data[(coluna*mtz->nrows)+linha] = let;
        return SUCESS;
    }
}

int matrizgetvalue (matriz *mtz, int linha, int coluna, unsigned char *let)
{
    if(mtz == NULL || mtz->data == NULL)
        return INVALID_NULL_POINTER;
    else if(linha < 0 || coluna < 0)
        return OUT_NOT_RANGE;
    else
    {
        (*let) = mtz->data[(coluna*mtz->nrows)+linha];
        return SUCESS;
    }
    
}

int linhas (matriz *mtz)
{
    if(mtz == NULL)
        return INVALID_NULL_POINTER;
    else
        return mtz->nrows;
}

int colunas (matriz *mtz)
{
    if(mtz == NULL)
        return INVALID_NULL_POINTER;
    else
        return mtz->ncols;
}

void freeMatriz(matriz *mtz)
{
    free(mtz->data);
    free(mtz);
}

