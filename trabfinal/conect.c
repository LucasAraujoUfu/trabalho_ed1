#include "fila/fifo.h"
#include "lib/Mat2d.h"
#include <stdlib.h>

matriz* image_conexa (matriz *img)
{
    if(img == NULL)
        return NULL;
    else
    {
        Fila *fi = criate_fila (size(img));
        if(fi == NULL)
        {
            freeMatriz(img);
            return NULL;
        }
        else
        {
            matriz *result = allocMatriz(linhas(img), colunas(img));
            if (result == NULL)
            {
                freequeue(fi);
                return NULL;
            }
            else
            {
                preenche_image(result);
                struct pixel px, temp;
                unsigned char aux, aux2, aux3;
                int codx, cody, cont=1;
                for(int lin = 1; lin < linhas(img); lin++)
                {
                    for(int col = 1; col < colunas(img); col++)
                    {
                        px.x = lin;
                        px.y = col;
                        matrizGetValue(img, lin, col, &aux);
                        matrizGetValue(result, lin, col, &aux2);

                        if(aux == 1 && aux2 == 0)
                        {
                            px.let = 1;
                            enqueue(fi, px);

                            while(empty_queue(fi) != SUCESS)
                            {
                                front_queue(fi, &px);
                                codx = px.x -1 ;
                                cody = px.y;
                                if(1 == pontos(img, codx, cody)
                                    && 0 == pontos(result, codx, cody)
                                    && dominio(img, codx, cody) == SUCESS)
                                {
                                    temp.let = 1;
                                    temp.x = codx;
                                    temp.y = cody;
                                    matrizSetValue(result, codx, cody, cont);
                                    enqueue(fi, temp);
                                }

                                codx = px.x +1;
                                cody = px.y;
                                if(1 == pontos(img, codx, cody)
                                    && 0 == pontos(result, codx, cody)
                                    && dominio(img, codx, cody) == SUCESS)
                                {
                                    temp.let = 1;
                                    temp.x = codx;
                                    temp.y = cody;
                                    enqueue(fi, temp);
                                    matrizSetValue(result, codx, cody, cont);
                                }

                                codx = px.x;
                                cody = px.y -1;
                                if(1 == pontos(img, codx, cody) &&
                                    0 == pontos(result, codx, cody) &&
                                    dominio(img, codx,cody) == SUCESS)
                                {
                                    temp.let = 1;
                                    temp.x = codx;
                                    temp.y = cody;
                                    enqueue(fi, temp);
                                    matrizSetValue(result, codx, cody, cont);
                                }

                                codx = px.x;
                                cody = px.y +1;
                                if(1 == pontos(img, codx, cody) &&
                                    0 == pontos(result, codx, cody) &&
                                    dominio(img, codx, cody) == SUCESS)
                                {
                                    temp.let = 1;
                                    temp.x = codx;
                                    temp.y = cody;
                                    enqueue(fi, temp);
                                    matrizSetValue(result, codx, cody, cont);
                                }
                                dequeue(fi);
                            }
                            cont++;
                        }
                    }
                }
                freequeue(fi);
                freeMatriz(img);
            }
            return result;
        }
    } 
}