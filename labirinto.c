#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void print_maze(char **maze, int largura, int altura) {

for (int i=0; i<13; i++ ){
  for (int j=0; j<10; j++ )
  {
     printf ("%d", maze[i][j]);
  }
printf("\n");
}
}

int labirinto(int x_atual, int y_atual,char **maze, int altura,int largura)
{
    if (x_atual < 0 || x_atual >= largura || y_atual < 0 || y_atual >= altura)
        return 0;

        char aqui = maze[x_atual][y_atual];

        if (aqui == 3)
        return 1;

        if(aqui == 0 || aqui == 2)
            return 0;


        maze[x_atual][y_atual] = 2;
         if(labirinto(x_atual ,y_atual-1,maze,altura,largura))return 1;


        maze[x_atual][y_atual] =2;
        if(labirinto(x_atual+1,y_atual,maze,altura,largura))return 1;



        maze[x_atual][y_atual] = 2;

        if(labirinto(x_atual,y_atual+1,maze,altura,largura))return 1;




        maze[x_atual][y_atual] = 2;
          if(labirinto(x_atual-1,y_atual,maze,altura,largura))return 1;



        maze[x_atual][y_atual] = 1;


            return 0;

}


int main(void)
{
char matriz [13][10]={
{0,0,0,0,0,0,0,0,0,0},
{0,0,1,1,1,1,1,0,0,0},
{0,0,1,0,0,0,1,0,0,0},
{0,0,1,0,0,0,1,0,0,0},
{1,1,1,0,1,1,1,1,1,0},
{0,1,0,0,1,0,0,0,0,0},
{0,1,1,0,1,1,1,0,0,0},
{0,0,1,0,1,0,0,0,1,0},
{0,0,1,0,0,0,1,1,1,0},
{0,0,1,1,1,1,1,0,0,0},
{0,0,0,0,0,0,1,0,0,0},
{0,0,0,0,0,0,1,1,1,3},
{0,0,0,0,0,0,0,0,0,0},};
int altura = 10;
int largura = 13;

char **a = malloc(largura * sizeof(char*));
for(int x = 0; x< largura; x++){
    a[x] = malloc(altura * sizeof(char));
}


for (int i=0; i<13; i++ ){
  for (int j=0; j<10; j++ )
  {
      a[i][j]= matriz[i][j];
  }
}

printf("ENTRADA");
print_maze(a,largura,altura);
int res =labirinto(4,0,a,altura,largura);
puts(res ?"Sucesso" : "Sem saida");
print_maze(a,largura,altura);

return 0;
}
