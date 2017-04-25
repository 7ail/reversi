/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1 
 * Full Name        : HAN LIANG ALVIN SEE
 * Student Number   : S3557766
 * Course Code      : COSC1076
 * Program Code     : BP094
 * Start up code provided by Paul Miller 
 **********************************************************************/

#include "utility.h"

/**
* function required to be used when clearing the buffer. It simply reads
* each char from the buffer until the buffer is empty again. Please refer
* to the materials on string and buffer handling in the course for more 
* information.
**/
void read_rest_of_line(void)
{
    int ch;
    while(ch = getc(stdin), ch != EOF && ch != NEWLINE)
        ;
    clearerr(stdin);
}

/*Prints the main menu*/
void print_main_menu(void)
{
    printf("Welcome to Reversi!\n");
    printf("===================\n");
    printf("Select an option:\n");
    printf("1. Play a game\n");
    printf("2. Display High Scores\n");
    printf("3. Quit the program\n");
    printf("Please enter your choice:\n");
}

void print_line(int length_of_line, char symbol)
{
	int i;
	for(i = 0; i < length_of_line; i++)
	{
		printf("%c", symbol);
	}
	printf("\n");
}