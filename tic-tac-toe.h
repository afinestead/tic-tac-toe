#ifndef	TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#define P1 'X'
#define P2 'O'
#define CLEAR ' '

#define P1_WIN  1
#define P2_WIN  2
#define DRAW    0
#define NO_WIN -1


void init_board(char board[3][3]);
void print_board1(char board[3][3]);
int  check_win(char board[3][3]);
void get_move(char board[3][3], int curr_depth, int stop_depth, int moves_table[9][3]);
int check_move(char board[3][3], char player, int curr_depth, int stop_depth);



#endif