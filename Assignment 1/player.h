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
#include "gameboard.h"
#include "utility.h"

#ifndef PLAYER_H
#define PLAYER_H
/* the maximum length of a player name */
#define NAMELEN 20
/* the number of characters allowed when the user is entering the coordinate
 * for a games
 */

/* what are the attributes of a player? They have a score, a token (either BLUE
 * or RED), and a score
 */
struct player
{
    char name[NAMELEN + 1];
    enum cell token;
    unsigned score;
};

/*Initialize the first player*/
BOOLEAN init_first_player(struct player* human, enum cell * token);
/*Initialize the second player*/
BOOLEAN init_second_player(struct player * computer, enum cell token);
/*Ask for the coordinates of the move and feed the data into the apply_move function*/
BOOLEAN make_move(struct player * player, game_board board);

#endif /* ifndef PLAYER_H */
