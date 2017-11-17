CC=gcc -g -std=c11 -Wall

# default target
tic-tac-toe: tic-tac-toe.o calculate_move.o get_player_move.o board.o
	$(CC) -o tic-tac-toe tic-tac-toe.o calculate_move.o get_player_move.o board.o


tic-tac-toe.o: tic-tac-toe.c tic-tac-toe.h
	$(CC) -c tic-tac-toe.c

board.o: board.c tic-tac-toe.h
	$(CC) -c board.c

calculate_move.o: calculate_move.c tic-tac-toe.h
	$(CC) -c calculate_move.c


get_player_move.o: get_player_move.c tic-tac-toe.h
	$(CC) -c get_player_move.c

.PHONY: clean
clean:
	rm -rf *.o
