/*=====*=====*=====*=====*=====*=====*=====*=====*=====*=====*/
/* CALCULATE_MOVE.C                                          */
/* This source file is for the tic-tac-toe game.             */
/* It contains functions necessary for the computer player   */
/* to make intelligent moves                                 */
/*                                                           */
/* Designed and tested by Alex Finestead                     */
/*=====*=====*=====*=====*=====*=====*=====*=====*=====*=====*/


#include "tic-tac-toe.h"

// Find optimal move for computer to make based on current board
// Recursively checks every possible outcome and creates table of moves
// Randomly selects move from list of "optimal" moves and makes move
// Takes current board state and a stop_depth integer for difficulty
// Returns integer of square computer will move to (1 - 9)
int get_computer_move(char board[3][3], int stop_depth, char player)
{
    int moves = 0;
    int moves_table[9][3] = { {0} };

    int row, column;
    for (row = 0; row < 3; row++)
    {
        for (column = 0; column < 3; column++)
        {
            // Log square in table
            moves_table[moves][0] = row;
            moves_table[moves][1] = column;

            // Only check empty squares (possible moves)
            if (board[row][column] == CLEAR)
            {
                // Test move
                board[row][column] = player;

                // calculate result of player moving to next spot
                if (player == P1)
                {
                    moves_table[moves][2] =
                            check_move(board, P2, 0, stop_depth);
                }

                else
                {
                    moves_table[moves][2] =
                            check_move(board, P1, 0, stop_depth);
                }

                // Clear out temp move
                board[row][column] = CLEAR;
            }

            // If move is impossible, log it as very undesirable
            else
            {
                moves_table[moves][2] = IMPOSSIBLE;
            }

            // Increment row in move table
            moves++;
        }
    }

    // Find strongest move from table
    int max = -50;
    int i;
    for (i = 0; i < 9; i++)
    {
        if (moves_table[i][2] > max)
        {
            max = moves_table[i][2];
        }
    }

    // Array to hold locations of strongest moves
    int optimal_moves[9] = {0};

    int num_optimal = 0;
    for (i = 0; i < 9; i++)
    {
        if (moves_table[i][2] == max)
        {
            optimal_moves[num_optimal] = i;
            num_optimal++;
        }
    }

    // If there is more than one optimal move, pick randomly
    // Creates games that are non-identical given same conditions
    int r = rand() % num_optimal;
    int optimal_row = moves_table[optimal_moves[r]][0];
    int optimal_column = moves_table[optimal_moves[r]][1];


    // Convert row/column pair to square (1-9) and return
    return ((optimal_column + 1) + (optimal_row * 3));
}




// Tries every possible board state and returns integer
// to indicate the strength of the move
// Takes board, player (P1/P2), current tree search depth,
// And the stop search depth (based on level selected)
// Function returns :
//      0 - 5 : Strong move (results in computer win)
//     -5 - 0 : Weak move (results in player win)
//      0     : Neutral move (results in draw or reached max search depth)
int check_move(char board[3][3], char player, int curr_depth, int stop_depth)
{
    // Check any end game scenarios with the current board
    int state = check_win(board);

    if (state == P2_WIN)
    {
        // Weight desirability based on how soon move shows up
        // If a win occurs on first move it will have greater weight
        return DESIRABLE - curr_depth;
    }

    if (state == P1_WIN)
    {
        // Losses are less desirable if they occur sooner
        return UNDESIRABLE - curr_depth;
    }

    // If draw, return a middle value
    if (state == DRAW)
    {
        return NEUTRAL;
    }

    // If reached level of complexity and no win/loss
    if (curr_depth >= stop_depth)
    {
        return NEUTRAL;
    }

    // Initialize best possible move to something impossible
    // Max outcome for Player is very negative
    int outcome = (player == P1) ? 50 : -50;

    // Try a move at every possible location
    int row, column;
    for (row = 0; row < 3; row++)
    {
        for (column = 0; column < 3; column++)
        {
            // Only check empty spaces (possible moves)
            if (board[row][column] == CLEAR)
            {
                // Set temporary move on board
                board[row][column] = player;

                int try_move;

                // If this is a computer move
                if (player == P2)
                {
                    // Check result of opposing player moving anywhere
                    try_move =
                        check_move(board, P1, (curr_depth + 1), stop_depth);

                    // If result is better than previous best, store it
                    if (try_move > outcome)
                    {
                        outcome = try_move;
                    }
                }

                // If this is a player move
                else
                {
                    // Check result of computer player moving anywhere
                    try_move =
                        check_move(board, P2, (curr_depth + 1), stop_depth);

                    if (try_move < outcome)
                    {
                        outcome = try_move;
                    }
                }

                // Clear out temp move
                board[row][column] = CLEAR;
            }
        }
    }

    return outcome;
}
