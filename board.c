/*=====*=====*=====*=====*=====*=====*=====*=====*=====*=====*/
/* BOARD.C                                                   */
/* This source file is for the tic-tac-toe game.             */
/* It contains functions relevant to printing the game board */
/* initializing the board, and checking if a game is over    */
/*                                                           */
/* Designed and tested by Alex Finestead                     */
/*=====*=====*=====*=====*=====*=====*=====*=====*=====*=====*/


#include "tic-tac-toe.h"

// Prints the current state of the board
// Takes board state as parameter
// Prints to stdout. No return
void print_board(char board[3][3], char last_move[30])
{
    printf("\t\t-------------------------\n");
    printf("\t\t|1      |2      |3      |\tYOU: '%c'\n", P1);
    printf("\t\t|   %c   |   %c   |   %c   |\n",
                board[0][0], board[0][1], board[0][2]);
    printf("\t\t|       |       |       |\tCOMPUTER: '%c'\n", P2);
    printf("\t\t-------------------------\n");
    printf("\t\t|4      |5      |6      |\n");
    printf("\t\t|   %c   |   %c   |   %c   |\n",
                board[1][0], board[1][1], board[1][2]);
    printf("\t\t|       |       |       |\t%s\n", last_move);
    printf("\t\t-------------------------\n");
    printf("\t\t|7      |8      |9      |\n");
    printf("\t\t|   %c   |   %c   |   %c   |\n",
                board[2][0], board[2][1], board[2][2]);
    printf("\t\t|       |       |       |\n");
    printf("\t\t-------------------------\n");
}


// Initalizes the board to empty
// Takes board array as parameter
// No return value
void init_board(char board[3][3])
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            board[i][j] = CLEAR;
        }
    }
}



// Function to check end game scenarios
// A "win" is determined to be 3 in a row of the same piece
// Takes current board state as parameter
// Returns integer to indicate scenario
//      1 : Player 1 wins
//      2 : Player 2 wins
//      0 : Draw
//     -1 : No win/draw
int check_win(char board[3][3])
{
    int row, column;

    // Check if any row is filled with same player
    for (row = 0; row < 3; row++)
    {
        if (board[row][0] == board[row][1] &&
            board[row][1] == board[row][2])
        {
            if (board[row][0] == P1)
            {
                return P1_WIN;
            }

            else if (board[row][0] == P2)
            {
                return P2_WIN;
            }
        }
    }

    // Check if any column is filled with same player
    for (column = 0; column < 3; column++)
    {
        if (board[0][column] == board[1][column] &&
            board[1][column] == board[2][column])
        {
            if (board[0][column] == P1)
            {
                return P1_WIN;
            }

            else if (board[0][column] == P2)
            {
                return P2_WIN;
            }
        }
    }

    // Check diagonal upper left to lower right
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
    {
        if (board[0][0] == P1)
        {
            return P1_WIN;
        }

        else if (board[0][0] == P2)
        {
            return P2_WIN;
        }
    }


    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
    {
        if (board[0][2] == P1)
        {
            return P1_WIN;
        }

        else if (board[0][2] == P2)
        {
            return P2_WIN;
        }
    }

    if (board[0][0] != ' ' && board[0][1] != ' ' && board[0][2] != ' ' &&
        board[1][0] != ' ' && board[1][1] != ' ' && board[1][2] != ' ' &&
        board[2][0] != ' ' && board[2][1] != ' ' && board[2][2] != ' ')
    {
        return DRAW;
    }

    // If no three in a row, return -1
    return NO_WIN;
}
