#include <stdio.h>
#include "tic-tac-toe.h"




int main(int argc, char** argv)
{

	init_board();
	print_board();

}


void print_board()
{
	int i, j;

	printf("\n\t\t");
	for (i = 0; i < 19; i++)
	{
		printf("-");
	}
	printf("\n");


	for (j = 0; j < 3; j++) 
	{
		printf("\t\t");
		for (i = 0; i < 19; i++) 
		{
			if ((i % 6) == 3)
			{
				printf("%c", board[j][i / 6]);
			}

			else if ((i % 3) == 0)
			{
				printf("|");
			}	

			else
			{
				printf(" ");
			}
		}
		printf("\n");

		printf("\t\t");
		for (i = 0; i < 19; i++)
		{
			printf("-");
		}
		printf("\n");
	} 
	printf("\n");
	
}

int check_win() 
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
				return 1;
			}

			else if (board[row][0] == P2)
			{
				return 2;
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
				return 1;
			}

			else if (board[0][column] == P2)
			{
				return 2;
			}
		}
	}

	// Check diagonal upper left to lower right
	if (board[0][0] == board[1][1] &&
		board[1][1] == board[2][2])
	{
		if (board[0][0] == P1)
		{
			return 1;
		}

		else if (board[0][0] == P2)
		{
			return 2;
		}
	}


	if (board[0][2] == board[1][1] &&
		board[1][1] == board[2][0])
	{
		if (board[0][2] == P1)
		{
			return 1;
		}

		else if (board[0][2] == P2)
		{
			return 2;
		}
	}

	// If no three in a row, return 0
	return 0;
}

void init_board()
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
