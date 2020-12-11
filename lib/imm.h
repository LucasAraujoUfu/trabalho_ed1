#ifndef IMMH
#define IMMH

#include "Mat2d.h"
#include "fifo.h"

matriz* image_conexa (matriz *img);

matriz *readTxt(char *s);
matriz *readImm(char *s);

int escreveMat(char *s, matriz *m);
int escreveImm(char *s,matriz *m);

matriz *segment(int thr,matriz *m);

int printMat(matriz *m);
int labirinto(int x_atual, int y_atual,unsigned char **maze, int altura,int largura);
#endif
