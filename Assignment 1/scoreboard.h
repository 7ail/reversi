/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1 
 * Full Name        : HAN LIANG ALVIN SEE
 * Student Number   : S3557766
 * Course Code      : COSC1076
 * Program Code     : BP094
 * Start up code provided by Paul Miller 
 **********************************************************************/

#include "shared.h"
#include "player.h"
#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#define MAX_SCORES 10
typedef struct player score;

/*Initialize the scoreboard*/
void init_scoreboard(score scores[MAX_SCORES]);
/*Checks if the winner's score qualifies for the scoreboard and if it does*/
/*adds them to the scoreboard*/
BOOLEAN add_to_scoreboard(score scores[MAX_SCORES], struct player * winner);
/*Prints the scoreboard*/
void display_scores(score scores[MAX_SCORES]);
#endif /* ifndef SCOREBOARD_H */
