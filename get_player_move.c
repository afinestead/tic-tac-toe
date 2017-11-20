/*=====*=====*=====*=====*=====*=====*=====*=====*=====*=====*/
/* GET_PLAYER_MOVE.C                                         */
/* This source file is for the tic-tac-toe game.             */
/* It contains functions necessary for the human player  to  */
/* make moves on the game board, including checking that a   */
/* move is legal.                                            */
/* User input is taken from stdin.                           */
/* Invalid entries are not accepted                          */
/*                                                           */
/* Designed and tested by Alex Finestead                     */
/*=====*=====*=====*=====*=====*=====*=====*=====*=====*=====*/


#include "tic-tac-toe.h"


// Gives player opportunity to select move
// Reads selection from stdin and checks validity of move
// Takes current board array as parameter
// Returns integer of square player is moving to (1 - 9)
int get_player_move(char board[3][3])
{
    char input_buffer[MAX_INPUT_SIZE];
    printf("\t\tPick a square to move to (1 - 9):  ");
    scanf("%2s", input_buffer);
    clear_stdin();

    int valid;

    // While the user enters an invalid move
    while ((valid = valid_move(input_buffer, board)) != VALID)
    {
        input_buffer[0] = '\0';

        if (valid == ERR_MULTIPLE_VALS)
        {
            printf("\t\tEnter a single value between 1 and 9:  ");
        }

        if (valid == ERR_INVALID_CHAR)
        {
            printf("\t\tEnter a single value between 1 and 9:  ");
        }

        if (valid == ERR_NON_EMPTY_SPACE)
        {
            printf("\t\tSpace is already taken. Choose another:  ");
        }

        scanf("%2s", input_buffer);
        clear_stdin();
    }

    // Convert char to integer and return
    return (input_buffer[0] - '0');
}


// Checks that the user has given a valid move
// Takes input string from stdin and current board
// Returns integer to indicate valididity or error
int valid_move(char input_buffer[MAX_INPUT_SIZE], char board[3][3])
{
    // If user entered more than one character
    if (input_buffer[1])
    {
        return ERR_MULTIPLE_VALS;
    }

    // If user enters a value other than 1-9
    if (input_buffer[0] < '1' || input_buffer[0] > '9')
    {
        return ERR_INVALID_CHAR;
    }

    // Convert char to integer
    int square = input_buffer[0] - '0';

    // Calculate row/column pair from single int
    int row = (square - 1) / 3;
    int column = (square - 1) % 3;

    // If the space is not empty, return 0
    if (board[row][column] != ' ')
    {
        return ERR_NON_EMPTY_SPACE;
    }

    // If passed all tests, return valid
    return VALID;
}
