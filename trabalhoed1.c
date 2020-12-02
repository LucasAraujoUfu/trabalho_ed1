#include <stdio.h>
int main (int argc, char* argv[])
{
    if(argc < 1)
        printf("digite o nome\n");
    else if(argc == 2)
    {
        printf("olá, %s seja bem vindo!\n",argv[1]);
    }
    return 0;
}