all:
	mkdir -p bin
	gcc -o bin/imm lib/fifo.c lib/Mat2d.c lib/imm.c main.c
fila:
	mkdir -p obj
	gcc -c lib/fifo.c -o obj/fifo.o
matriz:
	mkdir -p obj
	gcc -c lib/Mat2d.c -o obj/Mat2d.o
imm:
	mkdir -p obj
	gcc -c lib/imm.c -o obj/imm.o
main:
	mkdir -p obj
	gcc -c main.c -o obj/main.o
Obj:
	make fila
	make matriz
	make imm
	make main
stack:
	mkdir -p obj
	gcc -c lib/TStack.c -o obj/TStack.o
allObj:
	make Obj
	mkdir -p bin
	gcc -o bin/imm obj/fifo.o obj/Mat2d.o obj/imm.o obj/main.o
clean:
	rm obj/*.o bin/imm
