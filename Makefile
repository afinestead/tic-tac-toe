CC=gcc -g -std=c11 -Wall

# default target
tic-tac-toe: tic-tac-toe.o get_move.o
	$(CC) -o tic-tac-toe tic-tac-toe.o get_move.o


tic-tac-toe.o: tic-tac-toe.c tic-tac-toe.h
	$(CC) -c tic-tac-toe.c


get_move.o: get_move.c tic-tac-toe.h
	$(CC) -c get_move.c

.PHONY: clean
clean:
	rm -rf *.o
