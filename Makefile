all:
	@gcc -c main.c -o main.o
	@gcc -c ./lib/Mat2d.c -o Mat2d.o
	@gcc -o imm main.o Mat2d.o

main:
	@gcc -c trabmain.c -o trabmain.o
	@gcc -c ./TADimage/tadimage.c -o tadimage.o
	@gcc -c ./matriz/TADmatriz.c -o TADmatriz.o
	@gcc -o imm2 trabmain.o tadimage.o TADmatriz.o
	@echo ./imm2 juntamente com comandos

test:
	@gcc -c ./matriz/testmatriz.c -o testmatriz.o
	@gcc -c ./matriz/TADmatriz.c -o TADmatriz.o
	@gcc -o testmatriz.exe testmatriz.o TADmatriz.o
	@./testmatriz.exe

clean:
	@rm *.o