
#include "tic-tac-toe.h"

// Find optimal move for computer to make based on current board
// Recursively checks every possible outcome and creates table of moves
// Randomly selects move from list of "optimal" moves and makes move
// Takes current board state and a stop_depth integer for difficulty
// No return value
void calculate_move(char board[3][3], int stop_depth)
{	
	FORCE_STATE();

	int moves = 0;
	int moves_table[9][3] = {{0}};

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
				board[row][column] = P2;

				// calculate result of move and store in table
				moves_table[moves][2] = check_move(board, P1, 0, stop_depth);

				// Clear out temp move
				board[row][column] = CLEAR;
			}

			// If move is impossible, log it as very undesirable
			else
			{
				moves_table[moves][2] = -2;
			}

			// Increment row in move table 
			moves++;
		}
	}


	// Find the optimal move to make from the moves possible
	int max = -10;
	int i;
	for (i = 0; i < 9; i++)
	{
		if (moves_table[i][2] > max)
		{
			max = moves_table[i][2];
		}
	}
	printf("MAXIMUM IS %d\n", max);
	int optimal_moves[9][2] = {{0}};
	int num_optimal = 0;
	for (i = 0; i < 9; i++)
	{
		if (moves_table[i][2] == max)
		{
			optimal_moves[num_optimal][0] = moves_table[i][0];
			optimal_moves[num_optimal][1] = moves_table[i][1];
			num_optimal++;
		}
	}

	
	printf("ROW COL STR\n");
	printf("%d, %d, %d\n", moves_table[0][0], moves_table[0][1], moves_table[0][2]);
	printf("%d, %d, %d\n", moves_table[1][0], moves_table[1][1], moves_table[1][2]);
	printf("%d, %d, %d\n", moves_table[2][0], moves_table[2][1], moves_table[2][2]);
	printf("%d, %d, %d\n", moves_table[3][0], moves_table[3][1], moves_table[3][2]);
	printf("%d, %d, %d\n", moves_table[4][0], moves_table[4][1], moves_table[4][2]);
	printf("%d, %d, %d\n", moves_table[5][0], moves_table[5][1], moves_table[5][2]);
	printf("%d, %d, %d\n", moves_table[6][0], moves_table[6][1], moves_table[6][2]);
	printf("%d, %d, %d\n", moves_table[7][0], moves_table[7][1], moves_table[7][2]);
	printf("%d, %d, %d\n", moves_table[8][0], moves_table[8][1], moves_table[8][2]);

	printf("\nTHERE ARE %d OPTIMAL MOVES\n", num_optimal);

	printf("ROW COL STR\n");
	printf("%d, %d\n", optimal_moves[0][0], optimal_moves[0][1]);
	printf("%d, %d\n", optimal_moves[1][0], optimal_moves[1][1]);
	printf("%d, %d\n", optimal_moves[2][0], optimal_moves[2][1]);
	printf("%d, %d\n", optimal_moves[3][0], optimal_moves[3][1]);
	printf("%d, %d\n", optimal_moves[4][0], optimal_moves[4][1]);
	printf("%d, %d\n", optimal_moves[5][0], optimal_moves[5][1]);
	printf("%d, %d\n", optimal_moves[6][0], optimal_moves[6][1]);
	printf("%d, %d\n", optimal_moves[7][0], optimal_moves[7][1]);
	printf("%d, %d\n", optimal_moves[8][0], optimal_moves[8][1]);
	

	// Pick a random optimal move.
	// Get a random number between 0 and num_optimal
	int r = rand() % num_optimal;
	int optimal_row = optimal_moves[r][0];
	int optimal_column = optimal_moves[r][1];

	printf("I'm choosing move %d, %d\n", optimal_row, optimal_column);

	board[optimal_row][optimal_column] = P2;

}




// Tries every possible board state and returns integer
// to indicate the strength of the move
// Takes board, player (P1/P2), current tree search depth,
// And the stop search depth (based on level selected)
// Function returns :
//		 2 : Strong move (results in computer win)
//		 0 : Weak move (results in player win)
//		 1 : Neutral move (results in draw)
//	  else : Impossible move
int check_move(char board[3][3], char player, int curr_depth, int stop_depth)
{
	int state = check_win(board);

	int i;
	char tabs[5] = "";
	for (i = 0; i < curr_depth; i++)
	{
		tabs[i] = '\t';
	}
	printf("%s current depth: %d\n", tabs, curr_depth);
	printf("%s current state: %d\n", tabs, state);

	// If computer wins, return positive
	if (state == P2_WIN)
	{
		return 2;
	}
	// If player wins, return negative
	else if (state == P1_WIN)
	{
		return 0;
	}
	// If draw, return 0
	else if (state == DRAW)
	{
		return 1;
	}

	// If reached level of complexity and no win/loss
	// Return neutral move
	else if (curr_depth >= stop_depth)
	{
		return 1;
	}

	// Initialize best possible move to something impossible
	// Max outcome for Player is very negative
	int outcome = (player == P1) ? 5 : -5;

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
				printf("%schecking %c at {%d, %d}... (level %d)\n", tabs, player, row, column, curr_depth);

				// Run get_move function on temp board
				int try_move = (player == P1) ? check_move(board, P2, (curr_depth + 1), stop_depth)
											  : check_move(board, P1, (curr_depth + 1), stop_depth);

				
				// If this is a computer move
				if (player == P2)
				{	
					// If move is better than previous best
					if (try_move > outcome)
					{
						outcome = try_move;
					}
				}

				// If this is a player move
				else
				{
					// If moves is worse than previous worst
					if (try_move < outcome)
					{
						outcome = try_move;
					}
				}
				
				//printf("current best is %d\n", best_possible);
				// Clear out temp move
				board[row][column] = CLEAR;
			}
		}
	}

	return outcome;
}
