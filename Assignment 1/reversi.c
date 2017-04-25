/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1 
 * Full Name        : HAN LIANG ALVIN SEE
 * Student Number   : S3557766
 * Course Code      : COSC1076
 * Program Code     : BP094
 * Start up code provided by Paul Miller 
 **********************************************************************/

#include "reversi.h"

/**
 * the hear of the program. The main() function in particular should 
 * manage the main menu for the program.
 **/
int main(void)
{
    score scrboard[MAX_SCORES];

    struct player player_one;
    struct player player_two;
    struct player *winner = NULL;
    
    /*Boolean check for scoreboard*/
    BOOLEAN top_ten = FALSE;
    /*Boolean for main while loop*/
    BOOLEAN active = TRUE;

    char selection[3];
    char *selection_ptr = NULL;
    
    /*Value fed into switch statement*/
    int menu_selection = 0;

    /* initialise the scoreboard */
    init_scoreboard(scrboard);
    /* in a loop: display the main menu */
    while(active)
    {
        /*Prints the main menu*/
        print_main_menu();
        /* get the user's selection for the main menu*/
        if(fgets(selection, sizeof(selection), stdin) == NULL)
        {
            printf("Invalid input.\n");
            printf("Please input numbers between 1 to 3.\n\n");
            continue;
        }
        /*Clears the buffer if the input is too large*/
        if(selection[strlen(selection) - 1] != '\n')
    	{
    		read_rest_of_line();
    		/*Prompts for a valid input*/
            printf("Input too large - try again. \n");
            printf("Please input numbers between 1 to 3.\n\n");
    		continue;
    	}
        /*Cast user input into an int */
		menu_selection = (int) strtol(selection, &selection_ptr, 10);
        /*Feeds the int into the switch statement*/
        switch(menu_selection)
        {
            /*Play a game and add the winner to the scoreboard*/
            case 1: winner = play_game(&player_one, &player_two);
                    /*Checks if there is a winner*/
                    if(winner != NULL)
                    {
                        printf("The winner is: %s\n\n", winner->name);
                        /*Checks if they made the top 10*/
                        top_ten = add_to_scoreboard(scrboard, winner);
                        if(top_ten == TRUE)
                        {
                            printf("Congratulations.\n"); 
                            printf("%s made the top 10.\n", winner->name);
                            printf("Score added to the scoreboard.\n\n");
                        }
                    }
                    else
                    {
                        printf("There was no winner.\n\n");
                    }
                    break;
            /*Display scoreboard*/ 
            case 2: display_scores(scrboard);
                    break;
            /*Quit the program*/
            case 3: active = FALSE;
                    break;
            /*Default error message if the input is invalid*/
            default:printf("Invalid input.\n");
                    printf("Please input numbers between 1 to 3.\n\n");
        }
    }    
    return EXIT_SUCCESS;
}


