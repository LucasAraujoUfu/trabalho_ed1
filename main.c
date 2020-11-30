#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/Mat2d.h"

int main(int argc, char *argv[]){
	if(strcmp(argv[1],"-open")==0){
	
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
