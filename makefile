test : tmp.o test.o
	gcc -o test tmp.o test.o -lm
tmp.o : tmp.c tmp.h
	gcc -c tmp.c -o tmp.o
test.o : test.c tmp.h
	gcc -c test.c -o test.o
clean :	
	rm -rf test tmp.o test.o *.gch