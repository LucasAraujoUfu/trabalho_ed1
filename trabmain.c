#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./matriz/TADmatriz.h"
#include "./TADimage/tadimage.h"

void cod_erros (int res);

int main (int argc, char *argv[])
{
    int resultado;
    matriz *Mtz;
    if(argc == 1)
    {
        printf("deve digitar os comandos!\n");
    }
    else if(argc == 3)
    {
        if(strcasecmp(argv[1],"-open") == 0)
        {
            if(strcasecmp(argv[2],"FILE.txt") == 0)
            {
                // ./imm2 -open FILE.txt
                printf("./imm2 -open FILE.txt\n");
                resultado = cria_bin(argv[2]);
            }
            else if(strcmp(argv[2],"FILE.imm") == 0)
            {
                // ./imm2 -open FILE.imm
                printf("./imm -open FILE.imm\n");
                resultado = readbin(argv[2], Mtz);
                print_matriz(Mtz);
            }
        }
    }
    else if(argc == 4)
    {
        if(strcasecmp(argv[1],"-convert") == 0)
        {
            if(strcasecmp(argv[2],"FILE.txt") == 0)
            {
                if(strcasecmp(argv[3],"File.imm") == 0)
                {
                    // ./imm -convert file.imm file.txt
                    printf("./imm -convert file.txt file.imm\n");
                }
            }
        }
        else if(strcasecmp(argv[1],"-cc") == 0)
        {
            if(strcasecmp(argv[2],"segfile.imm") == 0)
            {
                if(strcasecmp(argv[3],"outfile") == 0)
                {
                    // -cc egfile.imm outfile
                    printf("./imm2 -cc egfile.imm outfile\n");
                }
            }
        }
        else if(strcasecmp(argv[1],"-lab") == 0)
        {
            if(strcasecmp(argv[2],"imlab.txt") == 0)
            {
                if(strcasecmp(argv[3],"imlabout.txt") == 0)
                {
                    // -lab imlab.txt imlabout.txt
                    printf("./imm2 -lab imlab.txt imlabout.txt\n");
                }
            }
        }
    }
    else if(argc == 5)
    {
        if(strcasecmp(argv[1],"-segment") == 0)
        {
            if(strcasecmp(argv[2],"thr") == 0)
            {
                if(strcasecmp(argv[3],"FILE.imm") == 0)
                {
                    if(strcasecmp(argv[4],"segfile.imm") == 0)
                    {
                        // -segment thr file.imm segfile.imm
                        printf("./imm2 -segment thr file.imm segfile.imm\n");
                    }
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < argc; i++)
        {
            printf("argv[%d] = %s\n",i,argv[i]);
        }
        printf("tamanho argc %d\n",argc);
    }
    printf("linhas %d\tcolunas %d\n",linhas(Mtz), colunas(Mtz));
    cod_erros (resultado);
    freeMatriz(Mtz);
    return 0;
}

void cod_erros (int res)
{
    switch (res)
    {
    case 0:
        printf("Operação finalizada com sucesso ;)\n");
        break;

    case -1:
        printf("Erro -> Ponteiro invalido!\n");
        break;

    case -2:
        printf("Erro -> Imcompatibilidade de tamanho!\n");
        break;

    case -3:
        printf("Erro -> Falta de memorya disponivel!\n");
        break;

    case -4:
        printf("Erro -> Entrada invalida!\n>");
        break;
    case -6:
        printf("Erro -> Na abertura na imagem!\n");
        break;

    default:
        break;
    }
}