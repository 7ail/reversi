/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1 
 * Full Name        : HAN LIANG ALVIN SEE
 * Student Number   : S3557766
 * Course Code      : COSC1076
 * Program Code     : BP094
 * Start up code provided by Paul Miller 
 **********************************************************************/
#include "player.h"
#include "game.h"

/**
 * These two functions initialise the player structure at the beginning of the 
 * game. In both cases, you should initialise the whole structure to known safe
 * values and then prompt the user for their name. In the init_first_player() 
 * function you should then select a color at random for this player using the 
 * rand() function. This token should be assigned to the first player's token and
 * also returned via the token pointer. In init_second_player() you should just
 * test the value of token and assign the opposite color to the second player.
 **/
BOOLEAN init_first_player(struct player* first, enum cell * token)
{
	char player1_name[NAMELEN + 2];
	/*Used for number randomizer*/
	int random_number;
	
	/* BOOLEAN value to be returned by the function */
	BOOLEAN init_player1;
	/* Local BOOLEAN for the while loop */
	BOOLEAN input = TRUE;
	
	/* Initializing to safe values */
	strcpy(first->name, "");
	first->token = 0;
	first->score = 0;
	
	/*Loops until a valid input is received or user explicitly ask to exit*/
	while(input == TRUE)
	{
		/*Ask for first player's name*/
		printf("Please enter the first player's name:\n");
		printf("Maximum length: 20\n");
		printf("Input enter or ctrl-d to quit or end the game.\n");
		/*Checks for ctrl-d input*/
		if(fgets(player1_name, sizeof(player1_name), stdin) == NULL)
		{
			printf("ctrl-d detected exiting game...\n\n");
			/*Breaks out of the local while loop*/
			input = FALSE;
			/*Returns boolean of FALSE at the end of the function*/
			init_player1 = FALSE;
		}
		/*Checks for enter input*/
		else if(player1_name[0] == NEWLINE)
		{
			printf("Enter detected exiting game...\n\n");
			/*Breaks out of the local while loop*/
			input = FALSE;
			/*Returns boolean of FALSE at the end of the function*/
			init_player1 = FALSE;
		}
		/*Checks if the length of the name is within 20 characters*/
		else if(player1_name[strlen(player1_name) - 1] != NEWLINE)
		{
			read_rest_of_line();
			printf("Invalid name. Please try again\n\n");
		}
		else
		{
			/*Copies the valid player name to first.name*/
			strcpy(first->name, player1_name);
			/*Sets the last character to null*/
			/*This is formatted mainly for the scoreboard*/
			first->name[strlen(first->name) - 1] = 0;
			/*Randomize a number between 0 and 1*/
			random_number = rand() % 2;
			/*Sets the token depending on the random number generated*/
			if(random_number == 0)
			{
				/*When this happens, this player goes first*/
				first->token = RED;
				/*Value is fed into the init_second_player function*/
				*token = BLUE;
			}
			else if(random_number == 1)
			{
				/*When this happens, this player goes second*/
				first->token = BLUE;
				/*Value is fed into the init_second_player function*/
				*token = RED;
			}
			/*Breaks out of the local while loop*/
			input = FALSE;
			/*Returns boolean of TRUE at the end of the function*/
			init_player1 = TRUE;
		}
	}
    return init_player1;
}

BOOLEAN init_second_player(struct player * second, enum cell token)
{
	char player2_name[NAMELEN + 2];

	/* BOOLEAN value to be returned by the function */
	BOOLEAN init_player2;
	/* Local BOOLEAN for the while loop */
	BOOLEAN input_two = TRUE;
	
	/* Initializing to safe values */
	strcpy(second->name, "");
	second->token = 0;
	second->score = 0;

	/*Loops until a valid input is received or user explicitly ask to exit*/
	while(input_two == TRUE)
	{
		/*Ask for second player's name*/
		printf("\nPlease enter the second player's name:\n");
		printf("Maximum length: 20\n");
		printf("Input enter or ctrl-d to quit or end the game.\n");
		/*Checks for ctrl-d input*/
		if(fgets(player2_name, sizeof(player2_name), stdin) == NULL)
		{
			printf("ctrl-d detected exiting game...\n\n");
			/*Breaks out of the local while loop*/
			input_two = FALSE;
			/*Returns boolean of FALSE at the end of the function*/
			init_player2 = FALSE;
		}
		/*Checks for enter input*/
		else if(player2_name[0] == NEWLINE)
		{
			printf("Enter detected exiting game...\n\n");
			/*Breaks out of the local while loop*/
			input_two = FALSE;
			/*Returns boolean of FALSE at the end of the function*/
			init_player2 = FALSE;
		}
		/*Checks if the length of the name is within 20 characters*/
		else if(player2_name[strlen(player2_name) - 1] != NEWLINE)
		{
			read_rest_of_line();
			printf("Invalid name. Please try again\n\n");
		}
		else
		{
			/*Copies the valid player name to second.name*/
			strcpy(second->name, player2_name);
			/*Sets the last character to null*/
			/*This is formatted mainly for the scoreboard*/
			second->name[strlen(second->name) - 1] = 0;
			/*Sets the second token to be the opposite of first player*/
			second->token = token;
			/*Breaks out of the local while loop*/
			input_two = FALSE;
			/*Returns boolean of TRUE at the end of the function*/
			init_player2 = TRUE;
		}		
	}
    return init_player2;
}

/**
* prompts the user for a comma-separate pair of coordinates for a move in the
* game. Each move, if valid, must capture at least one enemy piece by 
* surrounding a sequence of one or more enemy pieces with two pieces of our 
* own: one being the new piece to be placed and the other a piece already 
* on the board. This function then validates that a valid move has been entered
* calls the apply_move function to do the actual work of capturing pieces.
**/
BOOLEAN make_move(struct player * human, game_board board)
{
	char coordinates[5];
    char *coordinates_ptr;

    /* stores the x and y coordinates in and array of char*/
    char *coordinate_ints[2];
    int array_iterator;

    unsigned int x_int;
    char *x_int_ptr;

    unsigned int y_int;
    char *y_int_ptr;

    BOOLEAN m_move;

    BOOLEAN input = FALSE;
	while(input == FALSE)
	{
		x_int = 0;
	    y_int = 0;
		printf("It is %s's turn.\n", human->name);
	    printf("Please enter x and y coordinates separated by a comma for \n");
	    printf("the piece you wish to place: 3,5\n");
	    printf("Input enter or ctrl-d to quit or end the game.\n");
	    /*Checks for ctrl-d input*/
	    if(fgets(coordinates, sizeof(coordinates), stdin) == NULL)
	    {
	        printf("ctrl-d detected exiting game...\n\n");
	        /*Breaks the local while loop*/
	        input = TRUE;
	        /*Returns FALSE at the end of the function*/
	        m_move = FALSE;

	    }
	    /*Checks for enter input*/
	    else if(coordinates[0] == NEWLINE)
	    {
	        printf("Enter detected exiting game...\n\n");
	        /*Breaks the local while loop*/
	        input = TRUE;
	        /*Returns FALSE at the end of the function*/
	        m_move = FALSE;
	    }
	    /*Checks if the length of the name is within 3 characters*/
	    else if(coordinates[strlen(coordinates) - 1] != '\n')
	    {
	        read_rest_of_line();
	        printf("Input too large - try again. \n\n");
	    }
	    else
	    {
	        array_iterator = 0;
	        /*Iterates over the initial input and extracts the integers*/
	        /*Delimiter is set to only ','*/
	        coordinates_ptr = strtok(coordinates, ",");
	        while(coordinates_ptr != NULL)
	        {
	            coordinate_ints[array_iterator] = coordinates_ptr;
	            array_iterator++;
	            coordinates_ptr = strtok(NULL, ",");
	        }
	        /*Cast the integers extracted into two separate unsigned ints*/
	        x_int = (unsigned int) strtol(coordinate_ints[0], &x_int_ptr, 10);
	        y_int = (unsigned int) strtol(coordinate_ints[1], &y_int_ptr, 10);
	        /*Feeds the above variables into the apply_move function*/
	        m_move = apply_move(board, y_int, x_int, human->token);
	        /*Checks the boolean being returned by apply_move*/
	        if(m_move == FALSE)
	        {
	        	/*Ask for another coordinate if apply_move returns FALSE*/
	        	input = FALSE;
	        }
	        else
	        {
	        	/*Else, break the local while loop*/
	        	input = TRUE;
	        }
	    }
	}
    return m_move;
}