#include "tic-tac-toe.h"

int main(int argc, char** argv)
{
	// Will hold current board state for all games
	char board[3][3];

	// Integers to keep score of games 
	int games_played = 1;
	int num_p1_wins = 0;
	int num_p2_wins = 0;
	int num_draws = 0;

	int level = get_level(argc, argv);
	printf("level = %d\n", level);

	// Seed the random generator with address of board
	srand((unsigned) &board);

	// Integer to track user response to play again
	int playagain = YES;
	while (playagain == YES)
	{
		// Initialize board to blank before each game
		init_board(board);
		print_board(board);

		// Play a game and store the victor
		int winner = play_game(board, level);


		// play_game must terminate with either win, loss, or draw
		if (winner == P1_WIN)
		{
			printf("You win!\n");
			num_p1_wins++;
		}
		else if (winner == P2_WIN)
		{
			printf("You lose!\n");
			num_p2_wins++;
		}
		else 
		{
			printf("It's a draw!\n");
			num_draws++;
		}

		
		printf("Play again? (y/n):  ");
		char response[10];
		scanf("%s", response);

		// If user enters invalid response
		while (response[0] != 'y' && response[0] != 'Y' &&
			   response[0] != 'n' && response[0] != 'N')
		{
			printf("Invalid response, please type either 'y' or 'n':  ");
			scanf("%s", response);
		}

		if (response[0] == 'N' || response[0] == 'n')
		{
			playagain = NO;

			printf("\n--------FINAL SCORE--------\n\n");
			printf("\tPLAYER\tCOMPUTER\n");
			printf("WINS:\t  %d  \t   %d\n", num_p1_wins, num_p2_wins);
			printf("LOSSES:\t  %d  \t   %d\n", (games_played - num_p1_wins - num_draws), 
											   (games_played - num_p2_wins - num_draws));
			printf("DRAWS:\t       %d\n", num_draws);

			printf("\nThanks for playing!\n\n\n");
		}

		else
		{
			games_played++;
		}
		
	}

	/* TODO:
		Imporve UX
	*/
}

int play_game(char board[3][3], int level)
{
	int winner;
	while (1)
	{
		printf("\nYour turn...\n");
		get_player_move(board);
		print_board(board);
		if ((winner = check_win(board)) != NO_WIN)
		{
			return winner;
		}

		printf("\nComputer's turn...\n");
		calculate_move(board, level);
		print_board(board);
		if ((winner = check_win(board)) != NO_WIN)
		{
			return winner;
		}
	}
}


int get_level()
{
	printf("\t\tChoose a level of difficulty.\n");
	printf("\t\tEasy   Medium   Hard   Expert\n\n");
	printf("\t\tEnter choice here: ");

	char input_buffer[MAX_INPUT_SIZE];
	scanf("%s", input_buffer);

	make_lowercase(input_buffer);

	if (!strcmp(input_buffer, "easy"))
	{
		return EASY;
	}

	if (!strcmp(input_buffer, "medium"))
	{
		return MEDIUM;
	}

	if (!strcmp(input_buffer, "hard"))
	{
		return HARD;
	}

	if (!strcmp(input_buffer, "expert"))
	{
		return EXPERT;
	}

	printf("Invalid response. Difficulty set to default (medium)\n");
	return DEFAULT_DIFFICULTY;
}


void make_lowercase(char str[MAX_INPUT_SIZE])
{
	int i = 0;
	while (str[i])
	{
		str[i] = tolower(str[i]);
		i++;
	}
}

