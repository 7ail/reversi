/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1 
 * Full Name        : HAN LIANG ALVIN SEE
 * Student Number   : S3557766
 * Course Code      : COSC1076
 * Program Code     : BP094
 * Start up code provided by Paul Miller 
 **********************************************************************/

#include "scoreboard.h"

/**
* initalise the scoreboard so that the scores for each element of the array
* is set to 0.
**/
void init_scoreboard(score scores[MAX_SCORES])
{
	int i;
	/*Loops through the scores array*/
	/*Sets all of them to safe values*/
	for(i = 0; i < MAX_SCORES; i++)
	{
		strcpy(scores[i].name, "");
		scores[i].score = 0;
		scores[i].token = 0;
	}
}


/**
 * insert the top scorer from the last game played in sorted order according
 * to their score 
 **/
BOOLEAN add_to_scoreboard(score scores[MAX_SCORES], struct player * winner)
{
	int i = 0;
	int j = 0;
	BOOLEAN score_added = FALSE;

	/*Iterates through the scoreboard from top to bottom*/
	for(i = 0; i < MAX_SCORES; i++)
	{
		if(winner->score >= scores[i].score)
		{
			/*Iterates through the scoreboard from the bottom to top*/
			/*Stops at the slot right before i stopped*/
			for(j = (MAX_SCORES - 1); j > i; j--)
			{
				/*Replace the score of the current slot with the slot above it*/
				scores[j].score = scores[j - 1].score;
				/*Replace the name of the current slot with the slot above it*/
				strcpy(scores[j].name, scores[j - 1].name);
			}
			/*Replace the score of the i'th slot with the new winner*/
			scores[i].score = winner->score;
			/*Replace the name of the i'th slot with the new winner*/
			strcpy(scores[i].name, winner->name);
			/*Returbs TRUE*/
			score_added = TRUE;
			break;
		}
	}
	return score_added;
}

/**
* display the scores in the scoreboard according to their order. Your output
* should match that provided in the assignment specification.
**/
void display_scores(score scores[MAX_SCORES])
{
	int i = 0;
	int j = 0;
	int number_of_spaces = 0;
	int length_of_equals_line = 20;
	int length_of_minus_line = 28;
	char equals = '=';
	char minus = '-';

	printf("\nReversi - Top Scores\n");
	/*Prints '=' till the end of the row*/
	print_line(length_of_equals_line, equals);
	/*Prints '-' till the end of the row*/
	print_line(length_of_minus_line, minus);
	printf("Name                 | Score\n");
	/*Prints '-' till the end of the row*/
	print_line(length_of_minus_line, minus);
	/*Iterates through the scores array*/
	for(i = 0; i < MAX_SCORES; i++)
	{
		/*Prints out the desired data when score value does not equal 0*/
		if(scores[i].score != 0)
		{
			/*Prints the name*/
			printf("%s", scores[i].name);
			/*Allocates max length of the name + 1 for formatting purpose*/
			/*Alligns with the '|' from the previous printf statement*/
			number_of_spaces = (NAMELEN + 1) - strlen(scores[i].name);
			/*Fills in the remaining spaces before reaching '|'*/
			for (j = 1; j <= number_of_spaces; j++)
			{
				printf(" ");
			}
			/*Prints the score*/
			printf("| %d\n", scores[i].score);
		}
	}
	/*Prints '-' till the end of the row*/
	print_line(length_of_minus_line, minus);
	printf("\n");
}