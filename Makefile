all: nqueens test_list knights

list.o: list.c list.h
	gcc -c list.c

board.o: board.c board.h
	gcc -c board.c

nqueens: nqueens.c board.o list.o
	gcc -o nqueens nqueens.c board.c list.c

knights: knights.c board.o list.o
	gcc -o knights knights.c board.c list.c

test_list: test_list.c list.o board.o
	gcc -o test_list test_list.c board.o list.o

clean:
	rm *.o


