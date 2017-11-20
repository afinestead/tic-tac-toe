/*=====*=====*=====*=====*=====*=====*=====*=====*=====*=====*/
/* TIC-TAC-TOE.C                                             */
/* This is a classic game of tic-tac-toe written in C        */
/* This is a player v. computer game.                        */
/* At the beginning of the game, the user may select either  */
/* An easy or hard difficulty for the computer.              */
/* At game's completion, the user is promted to play again   */
/* or quit. If the user chooses to end the game, she or he   */
/* is shown the total score of all games played in the round */
/* The program then terminates.                              */
/*                                                           */
/* To run the program, compile with a "make" command         */
/* then use ./tic-tac-toe to begin.                          */
/*                                                           */
/* This game was designed and tested be Alex Finestead       */
/*=====*=====*=====*=====*=====*=====*=====*=====*=====*=====*/


#include "tic-tac-toe.h"
#include <unistd.h>
#include <ctype.h>
#include <time.h>

int main(int argc, char** argv)
{
    // Will hold current board state for all games
    char board[3][3];

    // Integers to keep scores on games
    int games_played = 0;
    int num_p1_wins = 0;
    int num_p2_wins = 0;
    int num_draws = 0;

    // Seed random number generator
    time_t t;
    srand((unsigned) time(&t));

    // Get the difficulty level from stdin
    int level = get_level();


    // Integer to track user response to continue playing
    int playagain = YES;

    while (playagain == YES)
    {
        // Increment total games played on each play through
        games_played++;

        // Clear the console window
        system("clear");
        printf("\n\n");

        // Initialize board to blank before each game
        init_board(board);
        print_board(board, "");

        // Play a game and store the victor
        int winner = play_game(board, level);


        // play_game must terminate with either win, loss, or draw
        if (winner == P1_WIN)
        {
            printf("\t\t\tYou win!\n\n");
            num_p1_wins++;
        }
        else if (winner == P2_WIN)
        {
            printf("\t\t\tYou lose!\n\n");
            num_p2_wins++;
        }
        else
        {
            printf("\t\t\tIt's a draw!\n\n");
            num_draws++;
        }

        // If user opts to end game, show the game stas
        if (!(playagain = get_play_again()))
        {
            show_stats(num_p1_wins, num_p2_wins, num_draws, games_played);
        }
    }
    return 0;
}


// Plays a game of tic-tac-toe
// Takes 3x3 char array for game board and an int representing difficulty
// Returns integer indicating outcome of the game upon completion
//      1 : Player 1 wins
//      2 : Player 2 wins
//      0 : Draw (no win)
int play_game(char board[3][3], int level)
{
    // Randomly select either P1 or P2 to go first
    int player = get_player();

    int winner, move;

    // Will hold last move as string and print on console
    char log_move[LOG_LINE_SIZE];

    while (1)
    {
        // Empty contents of last move
        strncpy(log_move, "", 30);

        if (player == P1)
        {
            printf("\n\t\tYour turn!\n\n");
            move = get_player_move(board);
        }
        else
        {
            printf("\n\t\tComputer's turn...\n\n");
            sleep(level / 2);  // Add delay based on complexity
            move = get_computer_move(board, level, player);

            // Capture move that computer made so it can be printed
            snprintf(log_move, LOG_LINE_SIZE, "Computer -> [%d]", move);
        }

        // Clear the console
        system("clear");

        // Add move to game board
        make_move(board, move, player);

        // Show current board
        printf("\n\n\n");
        print_board(board, log_move);
        printf("\n");

        // Switch turns to opposite player
        player = (player == P1) ? P2 : P1;

        // If board is showing an end game state
        if ((winner = check_win(board)) != NO_WIN)
        {
            return winner;
        }
    }
}



// Places move on the game board. No valid move checking.
// Takes 3x3 char array for game board, an int for the square
// being moved to, and a char to indicate P1 or P2
// No retrurn.
void make_move(char board[3][3], int move, char player)
{
    // Calculate row/column pair from square
    int row = (move - 1) / 3;
    int column = (move - 1) % 3;

    board[row][column] = player;
}



// Randomly select who gets to move first
// No parameters
// Returns char representing P1 or P2 (X or O)
char get_player()
{
    // Pick randomly P1 or P2 to go first
    int r = rand() % 2;

    // If r is 1, P1 goes first, else P2 goes first
    return (r ? P1 : P2);
}



// Let user select level of difficulty for the game
// Called at start of program just once
// This function is case insensitive
// If user enters something other than easy or hard, default level is set
// Takes no parameters
// Returns int for difficulty level selected
int get_level()
{
    printf("\n\n\n");
    printf("\t\t\t\tChoose a difficulty.\n");
    printf("\t\t\t\t   Easy      Hard   \n\n");
    printf("\t\t\t\tEnter choice here: ");

    char input_buffer[MAX_INPUT_SIZE];

    // Read max 4 chars from stdin ("easy"/"hard")
    scanf("%4s", input_buffer);
    clear_stdin();

    tolowerstr(input_buffer);

    if (!strcmp(input_buffer, "easy"))
    {
        return EASY;
    }

    if (!strcmp(input_buffer, "hard"))
    {
        return HARD;
    }

    printf("\t\tInvalid response. Difficulty set to default (easy).\n\n\n");
    return DEFAULT_DIFFICULTY;
}



// Prompts the user to play tic-tac-toe again
// Reads response from stdin
// Only looks at first character of response
// If response invalid, keep asking
// User must enter either a Y word or an N word
// Returns 1 if user wants to play again, 0 if not
int get_play_again()
{
    printf("\t\tPlay again? (y/n):  ");

    char response[4];
    scanf("%3s", response);
    clear_stdin();

    // If user enters invalid response
    while (response[0] != 'y' && response[0] != 'Y' &&
           response[0] != 'n' && response[0] != 'N')
    {
        printf("\t\tInvalid response, please type either 'y' or 'n':  ");
        scanf("%s", response);
        clear_stdin();
    }


    if (response[0] == 'N' || response[0] == 'n')
    {
        return NO;
    }
    else
    {
        return YES;
    }
}



// Show game statistics after completion of program
// Shows total number of wins, losses and draws for each player
// Takes integers for number of wins for p1 and p2,
// number of games drawn, and total number of games played
// Returns nothing
void show_stats(int p1_wins, int p2_wins, int draws, int games)
{
    printf("\n\n");
    printf("\t\t--------FINAL SCORE--------\n");
    printf("\t\t|                         |\n");
    printf("\t\t|\tPLAYER\tCOMPUTER  |\n");
    printf("\t\t| WINS:\t   %d  \t   %d\t  |\n", p1_wins, p2_wins);
    printf("\t\t| LOSSES:  %d  \t   %d\t  |\n", (games - p1_wins - draws),
                                           (games - p2_wins - draws));
    printf("\t\t| DRAWS:       %d   \t  |\n", draws);
    printf("\t\t---------------------------\n");

    printf("\n\t\t   Thanks for playing!\n\n\n");
}



// Flushes the stdin buffer so each read from stdin is clean
// Takes no parameters
// Returns nothing
void clear_stdin()
{
    char c;
    while ((c = getchar()) != '\n' && c != '\0');
}



// Forces string to be lowercase
// Runs through each char of string and uses tolower() func
// Takes string to convert to lowercase
// Lowercase is stored in original string
// No return
void tolowerstr(char* str)
{
    int i = 0;
    while (str[i])
    {
        str[i] = tolower(str[i]);
        i++;
    }
}


