#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./fila/fifo.h"
#include "./lib/Mat2d.h"
#include "conect.h"

matriz *readImm(char *s){
	FILE *f = fopen(s,"rb");
	if(f==NULL)return NULL;
	
	int lin,col;
	fread(&lin,sizeof(int),1,f);
	fread(&col,sizeof(int),1,f);
	
	matriz *m = allocMatriz(lin,col);
	if(m==NULL)return m;
	
	unsigned char c;
	for(int i=0;i<lin;i++){
		for(int j=0;j<col;j++){
			fread(&c,sizeof(unsigned char),1,f);
			int t = matrizSetValue(m,i,j,c);
			if(t<0)return NULL;
		}
	}
	
	fclose(f);
	return m;
}


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


matriz *segment(int thr,matriz *m){
	for(int i=0;i<linhas(m);i++){
		for(int j=0;j<colunas(m);j++){
			unsigned char c;
			int t = matrizGetValue(m,i,j,&c);
			if(t<0)return NULL;
			if(c>=thr)c=1;
			else c=0;
			t = matrizSetValue(m,i,j,c);
			if(t<0)return NULL;
		}
	}
	return m;
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
				freeMatriz(m);
			}
			else if(strstr(argv[2],".imm")!=NULL){
				matriz *m = readImm (argv[2]);
				if(m == NULL)
				{
					printf("ERROR, não foi possivel ler %s\n",argv[2]);
					exit(1);
				}
				else
				{
					int t = printMat (m);
					if(t < 0)
					{
						printf("ERROR, não foi possivel ler %s\n",argv[2]);
						exit(1);
					}
					else
					{
						printf("Operação finalizada com sucesso!\n");
						freeMatriz(m);
						return 0;
					}
				}
			}
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
		if(argc<5){
			printf("usage %s -segment [thr] [file.imm] [segfile.imm]\n",argv[0]);
		}
		else{
			matriz *m;
			if(strstr(argv[3],".txt")!=NULL){
				m = readTxt(argv[3]);
			}
			else if(strstr(argv[3],".imm")!=NULL){
				m = readImm (argv[3]);
			}
			int thr = atoi(argv[2]);
			m = segment(thr, m);
			escreveImm(argv[4],m);
		}

	}
	else if(strcmp(argv[1],"-cc")==0){
		if(strstr(argv[2], ".imm") != NULL)
		{
			matriz *img = readImm (argv[2]);
			if(strcmp(argv[3],"outfile") == 0)
			{
				if(img != NULL)
				{
					img = image_conexa(img);
					printMat(img);
				}
				else
					printf("erro!\n");
			}else
			{
				
			}
			freeMatriz(img);
			
		}
		else
		{
			printf("Comandos não encontrados");
			for (int i = 0; i < argc; i++)
			{
				printf("%s ",argv[i]);
			}
			
		}
		

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
	return 0;
}
