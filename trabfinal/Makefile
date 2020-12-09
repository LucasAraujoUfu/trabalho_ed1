all:
	@gcc -c conect.c -o conect.o
	@gcc -c ./fila/fifo.c -o fifo.o
	@gcc -c ./lib/Mat2d.c -o Mat2d.o
	@gcc -c main.c -o main.o
	@gcc -o imm  Mat2d.o fifo.o conect.o main.o

main:
	@gcc -c trabmain.c -o trabmain.o
	@gcc -c ./TADimage/tadimage.c -o ./TADimage/tadimage.o
	@gcc -c ./matriz/TADmatriz.c -o ./matriz/TADmatriz.o
	@gcc -o imm2 trabmain.o ./TADimage/tadimage.o ./matriz/TADmatriz.o
	@echo ./imm2 juntamente com comandos

test:
	@gcc -c ./TADimage/tadimage.c -o tadimage.o
	@gcc -c ./matriz/testmatriz.c -o testmatriz.o
	@gcc -c ./matriz/TADmatriz.c -o TADmatriz.o
	@gcc -o testmatriz.exe testmatriz.o TADmatriz.o tadimage.o
	@./testmatriz.exe

clean:
	@rm *.o
