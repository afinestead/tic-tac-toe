#include <stdio.h>
#include "tic-tac-toe.h"
#include <stdlib.h>


int main(int argc, char** argv)
{
	char board[3][3];
	init_board(board);

	board[0][0] = 'X';
	board[0][1] = 'O';
	board[0][2] = ' ';
	board[1][0] = 'O';
	board[1][1] = 'X';
	board[1][2] = ' ';
	board[2][0] = ' ';
	board[2][1] = ' ';
	board[2][2] = ' ';


	print_board1(board);

	int moves[9][3] = {0};
	get_move(board, 0, 1, moves);
	
	printf("ROW COL STR\n");
	printf("%d, %d, %d\n", moves[0][0], moves[0][1], moves[0][2]);
	printf("%d, %d, %d\n", moves[1][0], moves[1][1], moves[1][2]);
	printf("%d, %d, %d\n", moves[2][0], moves[2][1], moves[2][2]);
	printf("%d, %d, %d\n", moves[3][0], moves[3][1], moves[3][2]);
	printf("%d, %d, %d\n", moves[4][0], moves[4][1], moves[4][2]);
	printf("%d, %d, %d\n", moves[5][0], moves[5][1], moves[5][2]);
	printf("%d, %d, %d\n", moves[6][0], moves[6][1], moves[6][2]);
	printf("%d, %d, %d\n", moves[7][0], moves[7][1], moves[7][2]);
	printf("%d, %d, %d\n", moves[8][0], moves[8][1], moves[8][2]);


	/* TODO:
		SORT TABLE (top entries will be optimal)
		Randomize so that it plays a different game under same conditions
		Add user input
		Imporve UI
	*/
}


void print_board1(char board[3][3])
{
	printf("\t\t-------------------------\n");
	printf("\t\t|1      |2      |3      |\n");
	printf("\t\t|   %c   |   %c   |   %c   |\n", board[0][0], board[0][1], board[0][2]);
	printf("\t\t|       |       |       |\n");
	printf("\t\t-------------------------\n");
	printf("\t\t|4      |5      |6      |\n");
	printf("\t\t|   %c   |   %c   |   %c   |\n", board[1][0], board[1][1], board[1][2]);
	printf("\t\t|       |       |       |\n");
	printf("\t\t-------------------------\n");
	printf("\t\t|7      |8      |9      |\n");
	printf("\t\t|   %c   |   %c   |   %c   |\n", board[2][0], board[2][1], board[2][2]);
	printf("\t\t|       |       |       |\n");
	printf("\t\t-------------------------\n");
}


// Function to check end game scenarios
// Returns integer to indicate state
//		1 : Player 1 wins
//		2 : Player 2 wins
//		0 : Draw
//	   -1 : No win/draw 
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
