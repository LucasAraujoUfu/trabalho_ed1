#include "fifo.h"
#include <stdlib.h>
#include "../lib/Mat2d.h"


struct FIFO
{
    struct pixel *data;
    int size;
    int MAX;
};

Fila* criate_fila (int tamanho)
{
    Fila *Fi = (Fila*) malloc (sizeof(Fila));
    if(Fi != NULL)
    {
        Fi->data = (struct pixel*) malloc (tamanho*sizeof(struct pixel));
        if(Fi->data == NULL)
        {
            free(Fi);
            return NULL;
        }
        else
        {
            Fi->MAX = tamanho;
            Fi->size=0;
        }
    }
    return Fi;
}

void freequeue(Fila *fi)
{
    free(fi->data);
    free(fi);
}

int enqueue (Fila *Fi,struct pixel px)
{
    if(Fi == NULL)
        return INVALID_NULL_POINTER;
    else if(Fi->size == Fi->MAX)
        return OUT_NOT_RANGE;
    else
    {
        Fi->data[Fi->size] = px;
        Fi->size++;
        return SUCESS;
    }
}

int dequeue (Fila *Fi)
{
    if(Fi == NULL)
        return INVALID_NULL_POINTER;
    else
    {
        for (int i = 0; i < Fi->size; i++)
        {
            Fi->data[i] = Fi->data[i+1];
        }
        
        Fi->size--;
        return SUCESS;
    }
}

int front_queue (Fila *fi, struct pixel *px)
{
    if(fi == NULL)
        return INVALID_NULL_POINTER;
    else if(fi->size == 0)
        return OUT_NOT_RANGE;
    else
    {
        (*px) = fi->data[0];
        return SUCESS;
    }
}

int full_queue (Fila *Fi)
{
    if(Fi == NULL)
        return INVALID_NULL_POINTER;
    else if(Fi->size == Fi->MAX)
        return SUCESS;
    else
        return OUT_NOT_RANGE;
}

int empty_queue (Fila *Fi)
{
    if(Fi == NULL)
        return INVALID_NULL_POINTER;
    else if(Fi->size == 0)
        return SUCESS;
    else
        return OUT_NOT_RANGE;
}



