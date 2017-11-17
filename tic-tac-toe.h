#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef	TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#define P1 'X'
#define P2 'O'
#define CLEAR ' '

#define P1_WIN  1
#define P2_WIN  2
#define DRAW    0
#define NO_WIN -1

#define YES 1
#define NO  0

#define DEFAULT_DIFFICULTY 3
#define EASY 1
#define MEDIUM 2
#define HARD 4
#define EXPERT 5

#define MAX_INPUT_SIZE 50


#define FORCE_STATE() board[0][0] = ' ';\
					  board[0][1] = 'O';\
					  board[0][2] = ' ';\
					  board[1][0] = 'X';\
					  board[1][1] = 'X';\
					  board[1][2] = ' ';\
					  board[2][0] = ' ';\
					  board[2][1] = ' ';\
					  board[2][2] = ' '



// Initialize the board to all clear
void init_board(char board[3][3]);

// Display the current board state on the console
void print_board(char board[3][3]);

// Check end game scenarios of current board state
int  check_win(char board[3][3]);

// Calculate a move for the computer player
void calculate_move(char board[3][3], int stop_depth);

// Recursively check possible moves to determine optimal outcome
int check_move(char board[3][3], char player, int curr_depth, int stop_depth);

// Take input from stdin to get human player's move
void get_player_move(char board[3][3]);

// Verify that a move is valid
int valid_move(char input_buffer[MAX_INPUT_SIZE], char board[3][3]);

// Start game of tic-tac-toe.
// Returns winner when complete
int play_game(char board[3][3], int level);

// Get the level of difficulty from stdin
int get_level();

void make_lowercase(char* str);

#endif