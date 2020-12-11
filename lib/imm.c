#include <stdio.h>
#include <stdlib.h>

#include "imm.h"
#include "Mat2d.h"
#include "fifo.h"

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

matriz* image_conexa (matriz *img){
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

                                front_queue(fi, &px);
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


int labirinto(int x_atual, int y_atual,unsigned char **maze, int altura,int largura){
	if (x_atual < 0 || x_atual >= largura || y_atual < 0 || y_atual >= altura)
		return 0;

	char aqui = maze[x_atual][y_atual];

	if (aqui == 3)return 1;

	if(aqui == 0 || aqui == 2)return 0;


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
