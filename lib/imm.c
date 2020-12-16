#include <stdio.h>
#include <stdlib.h>

#include "imm.h"
#include "Mat2d.h"
#include "fifo.h"
#include "TStack.h"

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


int maze(int x_current, int y_current,matriz* m, int height,int width)
{
  Pilha *p;
  pilha_init(p);

  pilha_push(p, x_current, y_current);

  char here;
  while (pilha_pop(p, &x_current, &y_current))
  {
    if (x_current < 0 || x_current >= width || y_current < 0 || y_current >= height)
      continue;

 	matrizGetValue(m,x_current,y_current,&here);
	 
    if (here  == 3)
      break;
    if (here == 0 || here == 2)
      continue;

   matrizSetValue(m,x_current,y_current,2);
    pilha_push(p, x_current, y_current-1);
    pilha_push(p, x_current, y_current+1);
    pilha_push(p, x_current-1, y_current);
    pilha_push(p, x_current+1, y_current);
  }

  while (pilha_pop(p, &x_current, &y_current));
  return (here == 3);
}

int buscaEntrada(unsigned char **mt, int lin, int col, int *i, int *j){
	int i1=0,j1=0;
	if(mt==NULL)return -1;
	for(i1=0;i1<lin;i1++){
		if(mt[0][i1]==1){
			*i=i1;
			*j=0;
			return 0;
		}
	}
	for(i1=0;i1<lin;i1++){
		if(mt[col-1][i1]==1){
			*i=i1;
			*j=col-1;
			return 0;
		}
	}
	for(j1=0;j1<col;j1++){
		if(mt[j1][0]==1){
			*i=0;
			*j=j1;
			return 0;
		}
	}
	for(j1=0;j1<col;j1++){
		if(mt[j1][lin-1]==1){
			*i=lin-1;
			*j=j1;
			return 0;
		}
	}
}

int buscaSaida(unsigned char **mt, int lin, int col, int i, int j){
	int i1=0,j1=0;
	if(mt==NULL)return -1;
	for(i1=0;i1<lin;i1++){
		if(mt[0][i1]==1&&(j!=0||i1!=i)){
			mt[0][i1]==3;
			return 0;
		}
	}
	for(i1=0;i1<lin;i1++){
		if(mt[col-1][i1]==1&&(j!=col-1||i1!=i)){
			mt[col-1][i1]=3;
			return 0;
		}
	}
	for(j1=0;j1<col;j1++){
		if(mt[j1][0]==1&&(j1!=j||i!=0)){
			mt[j1][0]=3;
			return 0;
		}
	}
	for(j1=0;j1<col;j1++){
		if(mt[j1][lin-1]==1&&(j1!=j||i!=lin-1)){
			mt[j1][lin-1]=3;
			return 0;
		}
	}
}
