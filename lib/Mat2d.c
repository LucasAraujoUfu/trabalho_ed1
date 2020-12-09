#include "Mat2d.h"

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

void exitMaze(matriz* m){
  char* saida = malloc(2*sizeof(char));
  for(int i = 0; i<m->row; i++){
    if(m[i][0] == 1){
      saida[0] = i;
      saida[1] = 0;
    }
  }
  m[saida[i]][saida[0]] = 3;
}

void setexitMaze(matriz* m){
  char* saida = malloc(2*sizeof(char));
  for(int i = 0; i<m->row; i++){
    if(m[i][0] == 3){
      saida[0] = i;
      saida[1] = 0;
    }
  }
  m[saida[i]][saida[0]] = 2;
}

char* startMaze(matriz *m){
  char* entrada = malloc(2*sizeof(char));
  for(int i = 0; i<m->col; i++){
    if(m[0][i] == 1){
      entrada[0]=0;
      entrada[1] = i;
    }
  }
  return entrada;
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
