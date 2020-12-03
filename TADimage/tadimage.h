#ifndef TADIMAGE_H
#define TADIMAGE_H
#include "../matriz/TADmatriz.h"

#define SUCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_NOT_RANGE -2
#define OUT_NOT_MEMORY -3
#define INVALID_OPERATION -4
//
#define ERRO_IMAGE_OPEN -6

int readbin (char end[], matriz *Img);

int cria_bin (char end[]);

#endif