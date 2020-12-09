#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/Mat2d.h"

int FindExit(int x_atual, int y_atual,char **maze, int altura,int largura)
{

    if (x_atual < 0 || x_atual >= largura || y_atual < 0 || y_atual >= altura)
        return 0;

        char aqui = maze[x_atual][y_atual];

        if (aqui == 3)
        return 1;

        if(aqui == 0 || aqui == 2)
            return 0;


        maze[x_atual][y_atual] = 2;
         if(FindExit(x_atual ,y_atual-1,maze,altura,largura))return 1;
         if(FindExit(x_atual+1,y_atual,maze,altura,largura))return 1;
         if(FindExit(x_atual,y_atual+1,maze,altura,largura))return 1;
         if(FindExit(x_atual-1,y_atual,maze,altura,largura))return 1;


        else{
         maze[x_atual][y_atual] = 1;
         return 0;
        }
}

void labirinto(matriz *m){
 exitMaze(m);
 char entrada[2] = startMaze(m);
 int res = FindExit(entrada[0],entrada[1],&m,linhas(),colunas());
    puts(res ? "success!" : "no luck!");
setexitMaze(m);
printMat(m);
}


matriz *readTxt(char *s){
	FILE *f = fopen(s,"r");

	if(f==NULL)return NULL;

	unsigned char c;
	int lin=0, col=1;
	while(fscanf(f,"%c",&c)!=EOF){
		if(lin==1&&c=='\t')col++;
		if(c=='\n')lin++;
	}

	fseek(f,0,SEEK_SET);

	matriz *m = allocMatriz(lin,col);
	for(int i=0;i<lin;i++){
		for(int j=0;j<col;j++){
			fscanf(f,"%hhu",&c);
			int t = matrizSetValue(m,i,j,c);
			if(t<0)return NULL;
		}
	}

	fclose(f);
	return m;
}

int escreveMat(char *s, matriz *m){
	FILE *f = fopen(s,"w");
	if(f==NULL)return -1;
	unsigned char c;
	int l = linhas(m), col=colunas(m);
	for(int i=0;i<l;i++){
		for(int j=0;j<col;j++){
			int t = matrizGetValue(m,i,j,&c);
			if(t<0)return -1;
			fprintf(f,"%d",c);
			if(j<col-1)fprintf(f,"\t");
		}
		fprintf(f,"\n");
	}
	fclose(f);
}

int printMat(matriz *m){
	unsigned char c;
	for(int i=0;i<linhas(m);i++){
		for(int j=0;j<colunas(m);j++){
			int t = matrizGetValue(m,i,j,&c);
			if(t<0)return -1;
			printf("%3d ",c);
		}
		printf("\n");
	}
	return 0;
}

int main(int argc, char *argv[]){
	if(argc==1){
		printf("Usage: %s [args][files]\n\n",argv[0]);
		printf("Try: %s --help\n",argv[0]);
	}
	else if(strcmp(argv[1],"-open")==0){
		if(argc==2){
			printf("Especifique um arquivo para ser lido.\n");
		}
		else{
			int tam = strlen(argv[2]);
			if(strstr(argv[2],".txt")!=NULL){
				matriz *m = readTxt(argv[2]);
				if(m==NULL){
					printf("ERROR, não foi possivel ler %s\n",argv[2]);
				}
				int t = printMat(m);
				if(t<0){
					printf("ERROR, não foi possivel ler %s\n",argv[2]);
				}
			}
			else if(strstr(argv[2],".imm")!=NULL){}
			else{
				printf("O formato do arquivo %s é inconpativel\n", argv[2]);
			}
		}
	}
	else if(strcmp(argv[1],"-convert")==0){

	}
	else if(strcmp(argv[1],"-segment")==0){

	}
	else if(strcmp(argv[1],"-cc")==0){

	}
	else if(strcmp(argv[1],"-lab")==0){

	}
	else if(strcmp(argv[1],"--help")==0){
		printf("Usage: %s [args][files]\n\n",argv[0]);
		printf("options:\n");
		printf("-open    - Abre um arquivo *.txt ou *.imm\n");
		printf("-convert - Converte um arquivo *.txt para *.imm\n");
		printf("-cc      - Detecta os componentes conexos de uma imagem\n");
		printf("-lab [imlab.txt] [imlabout.txt] - Mostra o caminho a ser percorrido em um labirinto\n");
		printf("-segment [thr] [file.imm] [segfile.imm] - o Faz o thresholding com um valor [thr] da imagem [file.imm] e escreve [segfile.imm]\n\n");
	}
	else{
		printf("%s %s not found, try %s --help\n",argv[0],argv[1],argv[0]);
		printf("%s %s não encontrado, tente %s --help\n",argv[0],argv[1],argv[0]);
	}
}
