#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/Mat2d.h"
//#include "lib/fifo.h"
#include "lib/imm.h"


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
			else if(strstr(argv[2],".imm")!=NULL){
				matriz *m = readImm(argv[2]);
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
				m = readImm(argv[3]);
			}
			int thr = atoi(argv[2]);
			m = segment(thr,m);
			escreveImm(argv[4],m);
		}
	}
	else if(strcmp(argv[1],"-cc")==0){
		if(argc !=4){
			printf("usage: %s -cc [file.imm] [outfile.imm]\n",argv[0]);
			exit(1);
		}else{
			matriz *m = NULL;
			if(strstr(argv[2],".txt")!=NULL){
				m = readTxt(argv[2]);
			}
			else if(strstr(argv[2],".imm")!=NULL){
				m = readImm(argv[2]);
			}
			else{
				printf("Arquivo incompativel\n");
				exit(1);
			}
			if(m!=NULL){
				matriz *m1 = image_conexa(m);
				if(m1!=NULL){
					int t = escreveImm(argv[3],m1);
					if(t<0){
						printf("ERROR\n");
						exit(1);
					}
				}
				else{
					printf("ERROR\n");
					exit(1);
				}
			}
			else {
				printf("ERROR\n");
				exit(1);
			}
		}
	}
	else if(strcmp(argv[1],"-lab")==0){
		if(argc != 4){
			printf("usage: %s -lab [imlab.txt] [imlabout.txt]\n",argv[0]);
			exit(1);
		}
		else{
			matriz *m;
			if(strstr(argv[2],".txt")!=NULL){
				m = readTxt(argv[2]);
			}
			else if(strstr(argv[2],".imm")!=NULL){
				m = readImm(argv[2]);
			}
			else{
				printf("Arquivo incompativel\n");
				exit(1);
			}
			if(m!=NULL){
				unsigned char **mt = toArray(m);
				if(mt==NULL){
					printf("error\n");
					exit(1);
				}
				else{
					int i,j;
					int t = buscaEntrada(mt,linhas(m),colunas(m),&i,&j); 
					if(t<0){
						printf("ERROR\n");
						exit(1);
					}
					t = buscaSaida(mt,linhas(m),colunas(m),i,j);
					if(t<0){
						printf("ERROR\n");
						exit(1);
					}
					labirinto(j,i,mt,linhas(m),colunas(m));
					m = arrayToMatriz(mt,linhas(m),colunas(m));
					if(m==NULL){
						printf("ERROR\n");
						exit(1);
					}
					t = escreveMat(argv[3],m);
					if(t<0){
						printf("ERROR\n");
						exit(1);
					}
				}
			}
		}
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
