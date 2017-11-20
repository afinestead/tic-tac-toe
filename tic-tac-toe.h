/*=====*=====*=====*=====*=====*=====*=====*=====*=====*=====*/
/* TIC-TAC-TOE.H                                             */
/* This header file is for the tic-tac-toe game              */
/* It contains macro definitions and function declarations   */
/* for all those used in the tic-tac-toe program             */
/*                                                           */
/* Designed by Alex Finestead                                */
/*=====*=====*=====*=====*=====*=====*=====*=====*=====*=====*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef TIC_TAC_TOE_H
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

#define DESIRABLE   5
#define UNDESIRABLE -5
#define NEUTRAL     0
#define IMPOSSIBLE -20

#define DEFAULT_DIFFICULTY 2
#define EASY   2
#define HARD   5

#define ERR_MULTIPLE_VALS   2
#define ERR_INVALID_CHAR    0
#define ERR_NON_EMPTY_SPACE 3
#define VALID               1

#define MAX_INPUT_SIZE 5  // Largest input is "easy"
#define LOG_LINE_SIZE  30


// Initialize the board to all clear
// Takes 3x3 char array (board) as parameter
// No return
void init_board(char board[3][3]);


// Display the current board state on the console
// Takes char array (board) as parameter
// No return
void print_board(char board[3][3], char last_move[30]);


// Check end game scenarios of current board state
// Takes char array (board) as parameter
// Returns integer value to indicate state of board
//      2 : Player 2 wins
//      1 : Player 1 wins
//      0 : Draw
//     -1 : No end game state
int check_win(char board[3][3]);


// Calculates an optimal move for computer player
// Takes current board, an integer to stop searching tree (difficulty)
// and a char to indicate player whose move this is
// Returns an integer to indicate square computer is moving to
int get_computer_move(char board[3][3], int stop_depth, char player);


// Recursively check possible moves to determine optimal outcome
// Takes char array (board), char to indicate player,
// An int for the current tree search depth, and an int for stop search depth
// Returns int to indicate optimal move from a path on the tree
int check_move(char board[3][3], char player, int curr_depth, int stop_depth);


// Take input from stdin to get human player's move
// Takes board array as parameter
// Returns integer to indicate square player is moving to
int get_player_move(char board[3][3]);


// Updates board after move is made
// Takes 3x3 char array (board), integer for square being moved to,
// and char indicating player as parameters
// No return
void make_move(char board[3][3], int move, char player);


// Verify that a move is valid
// Takes string with user entered data and board as parameters
// Returns integer to indicate validity of move
int valid_move(char input_buffer[MAX_INPUT_SIZE], char board[3][3]);


// Start game of tic-tac-toe.
// Takes empty 3x3 char array (board) and int difficulty level as params
// Returns winner when game complete
int play_game(char board[3][3], int level);


// After game completion, show statistics for games played
// Takes number of player 1 wins, player 2 wins, draws,
// and total number of games played
// No return
void show_stats(int p1_wins, int p2_wins, int draws, int games);


// Get the level of difficulty from stdin
// No parameters
// Returns integer corresponding to difficulty selected
int get_level();


// Prompt the user to play again
// Reads user response from stdin
// Takes no parameters
// Returns 1 if yes, 0 if no
int get_play_again();


// Randomly selects either P1 or P2 to moves first
// No parameters
// Returns char indicating P1 or P2
char get_player();


// Convert string to all lowercase letters
// Takes string to convert to lowercase as param
// No return
void tolowerstr(char* str);


// Flushes stdin buffer to give clean scanf()
// No parameters, no return
void clear_stdin();

#endif  // TIC_TAC_TOE_H
