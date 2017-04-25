/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1 
 * Full Name        : HAN LIANG ALVIN SEE
 * Student Number   : S3557766
 * Course Code      : COSC1076
 * Program Code     : BP094
 * Start up code provided by Paul Miller 
 **********************************************************************/
#include <time.h>
#include "shared.h"
#include "player.h"
#include "gameboard.h"


#ifndef GAME_H
#define GAME_H

/*Initiates a new game*/
struct player * play_game(struct player * human, struct player * computer);
/*Validates user input (coordinates) and apply the move*/
BOOLEAN apply_move(game_board board, unsigned y, unsigned x,
                   enum cell player_token);
/*Checks the score of the players*/
unsigned game_score(game_board board, enum cell player_token);
/*Swaps the players at the end of their turns*/
void swap_players(struct player ** first, struct player ** second);

#endif /* ifndef GAME_H */
