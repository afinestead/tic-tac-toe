#ifndef	TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#define P1 'X'
#define P2 'O'
#define CLEAR ' '


char board[3][3];

void init_board();
void print_board();
int  check_win();

#endif