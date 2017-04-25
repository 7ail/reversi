/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1 
 * Full Name        : HAN LIANG ALVIN SEE
 * Student Number   : S3557766
 * Course Code      : COSC1076
 * Program Code     : BP094
 * Start up code provided by Paul Miller 
 **********************************************************************/
#include "gameboard.h"
#include "player.h"
#include "game.h"

/**
* initialise the game board to be consistent with the screenshot provided
* in your assignment specification. 
*
* All squares should be initialised to be blank other than the four
* squares in the middle of the board. In that case they are initialised to 
* appropriate colored tokens
**/

/*Prints player details*/
void print_player_details(struct player * first)
{
	char minus = '-';
	int short_line = 20;
	int j;
	int num_of_spaces;

	/*Prints '-' 20x*/
	print_line(short_line, minus);
	/*Prints the name*/
	printf("Name: %s", first->name);
	/*Prints " " in the remaining spaces to keep spacing constant*/
	num_of_spaces = (NAMELEN + 1) - strlen(first->name);
	for (j = 1; j <= num_of_spaces; j++)
	{
		printf(" ");
	}
	/*Depending on the token print in different colors*/
	if(first->token == RED)
	{
		printf("Token: %s0%s\t\t", COLOR_RED, COLOR_RESET);
	}
	else
	{
		printf("Token: %s0%s\t\t", COLOR_BLUE, COLOR_RESET);
	}
	/*Prints score*/
	printf("Score: %d\n", first->score);
	/*Prints '-' 80x*/
	print_line(LINELEN, minus);
}

void init_game_board(game_board board)
{
	int row;
	int column;

	int start_row_one = (BOARD_HEIGHT/2) - 1;
	int start_row_two = (BOARD_HEIGHT/2);
	int start_col_one = (BOARD_WIDTH/2) - 1;
	int start_col_two = (BOARD_WIDTH/2);

	printf("\n");
	/*Checks if BOARD_HEIGHT and BOARD_WIDTH are equal*/
	/*Checks if they are even*/
	if(BOARD_HEIGHT == BOARD_WIDTH && BOARD_HEIGHT % 2 == 0)
	{
		/*Iterates through the rows of the board*/
		for(row = 0; row < BOARD_HEIGHT; row++)
		{
			/*Iterates through the columns of the board*/
			for(column = 0; column < BOARD_WIDTH; column++)
			{
				/*Sets the starting top-right RED piece*/
				if((row == start_row_one) && (column == start_col_one))
				{
					board[row][column] = RED;
				}
				/*Sets the starting top-left BLUE piece*/
				else if((row == start_row_one) && (column == start_col_two))
				{
					board[row][column] = BLUE;
				}
				/*Sets the starting bottom-right BLUE piece*/
				else if((row == start_row_two) && (column == start_col_one))
				{
					board[row][column] = BLUE;
				}
				/*Sets the starting bottom-left BLUE piece*/
				else if((row == start_row_two) && (column == start_col_two))
				{
					board[row][column] = RED;
				}
				/*Sets the remaining cells to be BLANK*/
				else
				{
					board[row][column] = BLANK;
				}
			}
		}
	}
	/*Prints and error message if someone incorrectly alters the*/
	/*BOARD_WIDTH and BOARD_HEIGHT values*/
	else
	{
		printf("Initialisation of gameboard failed.\n");
		printf("Either BOARD_WIDTH != BOARD_HEIGHT or\n");
		printf("They are not even values\n");
	}
}

/**
* display the board as specified in the assignment specification. You should 
* make every effort to create a board consistent with the screenshots in the 
* assignment specification. 
**/
/* Need clarification for player * first and player * second */
void display_board(game_board board, struct player * first,
                   struct player * second)
{
	/*Counter to track the column being printed*/
	int col_ctr =0;
	/*Tracks the column numbering printed at the top of the board*/
	int col_nbr = 1;

	/*Counter to track the row being printed*/
	int row_ctr = 0;
	/*Tracks the row numbering printed at the left-side of the board*/
	int row_nbr = 1;

	/*Used to track the contents of board*/
	int y_coordinate = 0;
	int x_coordinate = 0;

	/*Used for printing format*/
	char equals = '=';

	/*Calculates the amount of printing space we need vertically*/
	int printed_board_height = (BOARD_HEIGHT + (BOARD_HEIGHT + 2));
	/*Calculates the amount of printing space we need horizontally*/
	int printed_board_width = (4 * (BOARD_WIDTH + 1));

	/*Calculates first player's score*/
	first->score = game_score(board, first->token);
	/*Calculates second player's score*/
	second->score = game_score(board, second->token);
	/*Credit to Alter Mann (StackOverflow)*/
	printf("\033[H\033[J");
	/*Prints '=' 80 times in a row*/
	print_line(LINELEN, equals);
	printf("Player One's Details\n");
	/*Prints player one's details*/
	print_player_details(first);

	printf("Player Two's Details\n");
	/*Prints player two's details*/
	print_player_details(second);

	/*Loops through the rows to be printed*/
	for(row_ctr = 1; row_ctr <= printed_board_height; row_ctr++)
	{
		/*Prints the first row of the board*/
		if(row_ctr == 1)
		{
			printf("  ");
			for(col_ctr = 1; col_ctr <= BOARD_WIDTH; col_ctr++)
			{
				/*Prints when the column number is a single digit*/
				if(col_nbr < 10)
				{
					printf("   %d", (col_nbr++));
				}
				/*Prints when the column number is more than a single digit*/
				else
				{
					printf("  %d", (col_nbr++));
				}
			}
		}
		/*Prints the "=" row*/
		else if(row_ctr == 2)
		{
			/*Prints "=" till the end of the row*/
			for(col_ctr = 1; col_ctr <= printed_board_width; col_ctr++)
			{
				printf("=");
			}
		}
		/*Prints the "-" on every even row starting from the 4th row*/
		else if((row_ctr != 2) && (row_ctr % 2 == 0))
		{
			/*Prints "-" till the end of the row*/
			for(col_ctr = 1; col_ctr <= printed_board_width; col_ctr++)
			{
				printf("-");
			}
		}
		/*Prints the rows with the cells that houses the tokens*/
		else
		{
			/*Iterates through the column*/
			for(col_ctr = 1; col_ctr <= printed_board_width; col_ctr++)
			{
				/*Prints the row number*/
				if(col_ctr == 1)
				{
					/*Prints when the row number is a single digit*/
					if(row_nbr < 10)
					{
						printf(" %d", row_nbr++);
						col_ctr+=1;
					}
					/*Prints when the row number is more than a single digit*/
					else
					{
						printf(" %d", row_nbr++);
						col_ctr+= 2;
					}
					
				}
				/*Prints "|" when col_ctr is a multiple of 4*/
				else if(col_ctr % 4 == 0)
				{
					printf("|");
				}
				/*Prints the contents of each cell*/ 
				/*Depends on the value in board*/
				else if(col_ctr % 2 == 0)
				{
					/*Prints " " if the value of board is BLANK*/
					if(board[y_coordinate][x_coordinate] == BLANK)
					{
						printf(" ");
						x_coordinate++;
					}
					/*Prints "0" in RED if the value of board is RED*/
					else if(board[y_coordinate][x_coordinate] == RED)
					{
						printf(COLOR_RED"0"COLOR_RESET);
						x_coordinate++;
					}
					/*Prints "0" in BLUE if the value of board is BLUE*/
					else if(board[y_coordinate][x_coordinate] == BLUE)
					{
						printf(COLOR_BLUE"0"COLOR_RESET);
						x_coordinate++;
					}
				}
				/*Prints " " for every other value of col_ctr*/
				else
				{
					printf(" ");
				}
			}
			/*Moves to the next row in the 2D board array*/
			y_coordinate++;
			/*Resets the column counter for the 2D board array*/
			x_coordinate = 0;
		}
		printf("\n");
	}
	printf("\n");
}

