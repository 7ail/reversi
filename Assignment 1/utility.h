#include "shared.h"
#include <limits.h>
#ifndef UTILITY_H
#define UTILITY_H

/* the default line length for input / output */
#define LINELEN 80

/* the last two characters required in a string as returned from fgets */
#define EXTRACHARS 2

/* newline character required for I/O functions */
#define NEWLINE '\n'

/*Clears the buffer reader*/
void read_rest_of_line(void);
/*Prints the main menu*/
void print_main_menu(void);
/*Prints a line with repeating elements*/
/*Used mainly in the scoreboard functions*/
void print_line(int length_of_line, char symbol);
#endif /* ifndef UTILITY_H */
