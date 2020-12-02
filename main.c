#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/Mat2d.h"

matriz *readTxt(char *s){
	FILE *f = fopen(s,"r");

	if(f==NULL)return NULL;

	unsigned char c;
	int lin=0, col=1;
	while(fscanf(f,"%c",&c)!=EOF){
		if(lin==1&&(c=='\t'||c==' '))col++;
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
	return 0;
}

int escreveImm(char *s,matriz *m){
	FILE * f = fopen(s,"wb");
	if(f==NULL)return -1;
	int l = linhas(m);
	fwrite(&l,sizeof(int),1,f);
	int c = colunas(m);
	fwrite(&c,sizeof(int),1,f);
	for(int i=0;i<l;i++){
		for(int j=0;j<c;j++){
			unsigned char u;
			matrizGetValue(m,i,j,&u);
			fwrite(&u,sizeof(unsigned char),1,f);
		}
	}
	fclose(f);
	return 0;
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
					exit(1);
				}
				int t = printMat(m);
				if(t<0){
					printf("ERROR, não foi possivel ler %s\n",argv[2]);
					exit(1);
				}
			}
			else if(strstr(argv[2],".imm")!=NULL){}
			else{
				printf("O formato do arquivo %s é inconpativel\n", argv[2]);
				exit(1);
			}
		}
	}
	else if(strcmp(argv[1],"-convert")==0){
		if(argc==2)printf("Especifique um arquivo para ser convertido\n");
		else if(strstr(argv[2],".txt")!=NULL){
			matriz *m = readTxt(argv[2]);
			if(m==NULL){
				printf("ERROR, não foi possivel ler %s\n",argv[2]);
				exit(1);
			}
			char *c = strstr(argv[2],".txt");
			c[1] = 'i';
			c[2] = 'm';
			c[3] = 'm';
			escreveImm(argv[2],m);	
		}
		else{
			printf("O formato do arquivo %s é inconpativel\n", argv[2]);
		}
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
