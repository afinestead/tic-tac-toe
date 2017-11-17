#include "tic-tac-toe.h"

// Gives player opportunity to select move
// Reads selection from stdin and checks validity of move
// Takes current board array as parameter
// No return value
void get_player_move(char board[3][3])
{
	char input_buffer[MAX_INPUT_SIZE];
	printf("Pick a square to move to (1 - 9):  ");
	scanf("%s", input_buffer);

	// While the user enters an invalid move
	while (!valid_move(input_buffer, board))
	{
		input_buffer[0] = '\0';
		printf("Enter a single value between 1 and 9:  ");
		scanf("%s", input_buffer);
	}

	// Convert char to integer
	int square = input_buffer[0] - '0';

	// Calculate row/column pair from single int
	int row = (square - 1) / 3;
	int column = (square - 1) % 3;	
	
	board[row][column] = P1;
}


// Checks that the user has given a valid move
// Takes input string from stdin and current board
// Returns integer to indicate valid (1) or invalid (0)
int valid_move(char input_buffer[MAX_INPUT_SIZE], char board[3][3])
{
	// If user entered more than one character
	if (input_buffer[1])
	{
		return 0;
	}

	// If user enters a value other than 1-9
	if (input_buffer[0] < '1' || input_buffer[0] > '9')
	{
		return 0;
	}

	// Convert char to integer
	int square = input_buffer[0] - '0';	

	// Calculate row/column pair from single int
	int row = (square - 1) / 3;
	int column = (square - 1) % 3;

	// If the space is not empty, return 0
	if (board[row][column] != ' ')
	{
		return 0;
	}
	// Else space is free, return 1
	else
	{
		return 1;
	}
}
