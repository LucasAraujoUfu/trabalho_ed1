#include "Mat2d.h"
#include <stdio.h>

struct matriz{
  int col;
  int row;
  unsigned char *data;
};

matriz* allocMatriz(int i, int j){
  if(i<=0||j<=0)return NULL;
  matriz *m;
  m = (matriz*)malloc(sizeof(matriz));
  m->row=i;
  if(m==NULL)return NULL;
  m->col=j;
  m->data = malloc(sizeof(unsigned char)*i*j);
  if(m->data==NULL){
    free(m);
    return NULL;
  }
  return m;
}

void freeMatriz(matriz* m){
  free(m->data);
  free(m);
}

int matrizSetValue(matriz *m,int i,int j,unsigned char n){
  if(i>m->row||i<0||j>m->col||j<0)return -1;
  if(m==NULL)return -1;
  if(m->data == NULL)return -1;
  m->data[j*m->row+i]=n;
  return 0;
}

int matrizGetValue(matriz *m,int i,int j,unsigned char *n){
  if(i<0||j<0||j>=m->col||i>=m->row)return -1;
  if(m==NULL)return -1;
  if(m->data == NULL)return -1;
  *n = m->data[j*m->row+i];
  return 0;
}

int linhas(matriz *m){
  if(m==NULL)return -1;
  return m->row;
}

int colunas(matriz *m){
  if(m==NULL)return -1;
  return m->col;
}

int size (matriz *m){
  if(m == NULL)return -1;
  else return (m->row * m->col);
}

unsigned char pontos (matriz *m, int i, int j){
  if(m == NULL)return '0';
  else if(i < 0 || j < 0 || i >= m->row || j >= m->col)return '0';
  else{
    return m->data[j*m->row+i];
  }
}

int preenche_image (matriz *img){
  if(img == NULL)return -1;
  else{
    for (int i = 0; i < img->row; i++){
      for (int j = 0; j < img->col; j++){
        img->data[(j*img->row)+i] = 0;
      }
    }
    return 0;
  }
}

int dominio (matriz *m,int x,int y){
  if(m == NULL)return -1;
  else if (x < 0 || x >  m->row || y < 0 || y > m->col)return -1;
  else return 0;
}

unsigned char **toArray(matriz *m){
	if(m==NULL)return NULL;
	unsigned char **mt = malloc(m->col * sizeof(unsigned char*));
	if(mt!=NULL){
		for(int x = 0; x<m->col;x++){
			mt[x] = malloc(m->row * sizeof(unsigned char));
			if(mt[x]==NULL){
				for(int j=0;j<x;j++){
					free(mt[j]);
				}
				free(mt);
				return NULL;
			}
		}
		for(int j=0;j<m->col;j++){
			for(int i=0;i<m->row;i++){
				int t = matrizGetValue(m,i,j,&mt[j][i]);
				//printf("%d %d\n",i,j);
				if(t<0){
					for(int k=0;k<m->col;k++){
						free(mt[k]);
					}
					free(mt);
					return NULL;
				}
			}
		}
	}
	return mt;
}

matriz *arrayToMatriz(unsigned char **mt, int lin,int col){
	matriz *m = allocMatriz(lin,col);
	
	for(int i=0;i<lin;i++){
		if(mt[i]==NULL){
			freeMatriz(m);
			return NULL;
		}
		for(int j=0;j<col;j++){
			int t = matrizSetValue(m,i,j,mt[j][i]);
			if(t<0){
				freeMatriz(m);
				return NULL;
			}
		}
	}
	return m;
}
