#include "tic-tac-toe.h"
#include <stdlib.h>
#include <stdio.h>


void get_move(char board[3][3], int curr_depth, int stop_depth, int moves_table[9][3])
{	

	int moves = 0;

	int row, column;
	for (row = 0; row < 3; row++)
	{
		for (column = 0; column < 3; column++)
		{
			// Only check empty squares (possible moves)
			if (board[row][column] == CLEAR)
			{

				printf("#############  NEW ITERATION ##############\n");
				// Test move
				board[row][column] = P2;
				printf("Trying this board...\n");
				print_board1(board);

				moves_table[moves][0] = row;
				moves_table[moves][1] = column;
				moves_table[moves][2] = check_move(board, P1, 0, 5);

				// Clear out temp move
				board[row][column] = CLEAR;
			}

			// If move is impossible, log it as very undesirable
			else
			{
				moves_table[moves][0] = row;
				moves_table[moves][1] = column;
				moves_table[moves][2] = -5;
			}
			// Increment row in move table 
			moves++;
		}
	}
}




// Tries every possible board state and returns integer
// to indicate the strength of the move
// Function returns :
//		 1 : Strong move (results in comp. win)
//		-1 : Weak move (results in player win)
//		 0 : Neutral move (results in draw)
int check_move(char board[3][3], char player, int curr_depth, int stop_depth)
{
	int state = check_win(board);

	// If computer wins, return positive
	if (state == P2_WIN)
	{
		return 1;
	}
	// If player wins, return negative
	else if (state == P1_WIN)
	{
		return -1;
	}
	// If draw, return 0
	else if (state == DRAW)
	{
		return 0;
	}

	// If reached level of complexity and no win/loss
	// Return neutral move
	else if (stop_depth == curr_depth)
	{
		return 0;
	}

	// Initialize best possible move to something impossible
	int best_possible = (player == P1) ? 5 : -5;

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
				printf("checking %c at {%d, %d}... (level %d)\n", player, row, column, curr_depth);
				print_board1(board);

				// Run get_move function on temp board
				int try_move = (player == P1) ? check_move(board, P2, (curr_depth + 1), stop_depth)
											  : check_move(board, P1, (curr_depth + 1), stop_depth);

				

				// If this is a computer move
				if (player == P2)
				{
					if (try_move > best_possible)
					{
						best_possible = try_move;
					}
				}

				// If this is a player move
				else
				{
					if (try_move < best_possible)
					{
						best_possible = try_move;
					}
				}
				
				printf("current best is %d\n", best_possible);
				// Clear out temp move
				board[row][column] = CLEAR;
			}
		}
	}

	return best_possible;
}
