/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1 
 * Full Name        : HAN LIANG ALVIN SEE
 * Student Number   : S3557766
 * Course Code      : COSC1076
 * Program Code     : BP094
 * Start up code provided by Paul Miller 
 **********************************************************************/
#include "game.h"

/**
 * The heart of the game itself. You should do ALL initialisation required 
 * for the game in here or call function required for that purpose. For example
 * both players should be initialised from here, you should seed the random 
 * number generator, that kind of thing. 
 *
 * Next, you should set the initial player - the initial player is the player 
 * whose token was set by initialisation to RED. 
 *
 * Next, you will need to manage the game loop in here. In each loop of the 
 * game, you should display the game board, including player scores 
 * display whose turn it is, etc in the format specified in the assignment
 * specification. Finally at the end of each turn you will calculate the score
 * for each player you will calculate their score and store it and then you 
 * will need to swap the current player and other player 
 * using the swap_player() function. 
 * 
 * A game will end when either player presses enter or ctrl-d on a newline. 
 * 
 * When you detect a request to end the game, you should do a final calculation
 * of the scores for the two players and return the player with the highest
 * score.
 **/
struct player * play_game(struct player * first, struct player * second)
{
	
	game_board board;
	enum cell token;
	struct player * current, *other, *winner;
	struct player **swap_current = &current;
	struct player **swap_other = &other;
	
	BOOLEAN init_first_success;
	BOOLEAN init_second_success;

	BOOLEAN game_active = TRUE;

	/*Initiate first player*/
	init_first_success = init_first_player(first, &token);
	/*Checks if successful*/
	if(init_first_success == TRUE)
	{
		/*Initiate second player*/
		init_second_success = init_second_player(second, token);
		/*Checks if successful*/
		if(init_second_success == TRUE)
		{
			/*Assigns the player with the first move depending on the token*/
			if(first->token == RED)
			{
				current = first;
				other = second;
			}
			else
			{
				current = second;
				other = first;
			}
			/*Initiate the gameboard*/
			init_game_board(board);
			do
			{
				/*Display board*/
				display_board(board, first, second);
				/*Calls make_move function*/
				/*If it returns FALSE, breaks the do-while loop*/
				/*Indicates end of game*/
				game_active = make_move(current, board);
				/*Swaps the player's turn*/
				swap_players(swap_current, swap_other);
			}
			while(game_active == TRUE);
			/*Checks if both the players have the same score*/
			if(first->score == second->score)
			{
				winner = NULL;
			}
			/*Checks if the first player scored higher than the second player*/
			else if(first->score > second->score)
			{
				/*Sets the winner to be the first player*/
				winner = first;
			}
			/*Checks if the second player scored higher than the first player*/
			else
			{
				/*Sets the winner to be the second player*/
				winner = second;
			}
		}
		/*Happens when player exits when initializing second player*/
		else
		{
			printf("Exited the game while initializing second player.\n");
			winner = NULL;
		}
	}
	/*Happens when player exits when initializing first player*/
	else
	{
		printf("Exited the game while initializing first player.\n");
		winner = NULL;
	}
	return winner;
}

/**
 * does the work of applying the move requested by the user to the game board.
 * It iterates over all the directions from the coordinate specified to see
 * whether there are any pieces that can be captured. If there are no pieces
 * that can be captured in any direction, it is an invalid move.
 **/
BOOLEAN apply_move(game_board board, unsigned y, unsigned x,
                   enum cell player_token)
{
	enum direction dir;
	unsigned captured_pieces = 0;
	BOOLEAN successful_move;

	int x_current;
	int x_decre;
	int x_incre;
	int x_adj;

	int y_current;
	int y_decre;
	int y_incre;
	int y_adj;

	if(x >= 1 && x <= BOARD_WIDTH && y >= 1 && y <= BOARD_HEIGHT)
    {
		x_current = x - 1;
		y_current = y - 1;
		if(board[y_current][x_current] == BLANK)
		{
			for(dir = NORTH; dir <= SOUTH_WEST; dir++)
			{
				switch (dir)
				{
					case NORTH: /*Gets the coordinate for the*/
								/*adjacent NORTH tile */
								/*Decrements the y-axis*/
								y_adj = y_current - 1;
								/*x-axis stays constant*/
								x_adj = x_current;
								/*Checks if the adjacent tile is BLANK or of*/ 
								/*the same token */
								if(board[y_adj][x_adj] != BLANK && 
								   board[y_adj][x_adj] != player_token)
								{
									/*Starts a for loop on the tile adjacent*/
									/*to the previously defined adjacent tile*/
									/*Decrement the y-axis to the max of 0*/
									for(y_decre = (y_current - 2); 
										y_decre >= 0; 
										y_decre--)
									{
										/*If the tile is BLANK, break for loop*/
										/*Nothing changes on the board*/
										if(board[y_decre][x_adj] == BLANK)
										{
											break;
										}
										/*If the tile has same player token*/
										/*Capture move becomes valid*/
										else if(board[y_decre][x_adj] 
											    == player_token)
										{
											/*Retracts steps on the board*/
											/*Sets them to the player token*/
											/*Starts from the previously*/
											/*iterated tile*/
											for(y_decre = (y_decre + 1); 
												y_decre < y_current; 
												y_decre++)
											{
												board[y_decre][x_adj] 
												= player_token;
												captured_pieces += 1;
											}
											break;
										}
										else
										{
											continue;
										}
									}
								}						
								break;
					case SOUTH: /*Gets the coordinate for the*/
								/*adjacent SOUTH tile */
								/*Decrements the y-axis*/
								y_adj = y_current + 1;
								/*x-axis stays constant*/
								x_adj = x_current;
								/*Refer to NORTH case for logic*/
								if(board[y_adj][x_adj] != BLANK && 
								   board[y_adj][x_adj] != player_token)
								{
									for(y_incre = (y_current + 2); 
										y_incre <= BOARD_HEIGHT; 
										y_incre++)
									{
										if(board[y_incre][x_adj] == BLANK)
										{
											break;
										}
										else if(board[y_incre][x_adj] 
												== player_token)
										{
											for(y_incre = (y_incre - 1); 
												y_incre > y_current; 
												y_incre--)
											{
												board[y_incre][x_adj] 
												= player_token;
												captured_pieces += 1;
											}
											break;
										}
										else
										{
											continue;
										}
									}
								}						
								break;
					case EAST: 	/*Gets the coordinate for the*/
								/*adjacent EAST tile */
								/*y-axis stays constant*/
								y_adj = y_current;
								/*Increments the x-axis*/
								x_adj = x_current + 1;
								/*Refer to NORTH case for logic*/
								if(board[y_adj][x_adj] != BLANK && 
								   board[y_adj][x_adj] != player_token)
								{
									for(x_incre = (x_current + 2); 
										x_incre <= BOARD_WIDTH; 
										x_incre++)
									{
										if(board[y_adj][x_incre] == BLANK)
										{
											break;
										}
										else if(board[y_adj][x_incre] 
												== player_token)
										{
											for(x_incre = (x_incre - 1); 
												x_incre > x_current; 
												x_incre--)
											{
												board[y_adj][x_incre] 
												= player_token;
												captured_pieces += 1;
											}
											break;
										}
										else
										{
											continue;
										}
									}
								}
								break;
					case WEST: 	/*Gets the coordinate for the*/
								/*adjacent WEST tile */
								/*y-axis stays constant*/
								y_adj = y_current;
								/*Decrements the x-axis*/
								x_adj = x_current - 1;
								/*Refer to NORTH case for logic*/
								if(board[y_adj][x_adj] != BLANK && 
								   board[y_adj][x_adj] != player_token)
								{
									for(x_decre = (x_current - 2); 
										x_decre >= 0; 
										x_decre--)
									{
										if(board[y_adj][x_decre] == BLANK)
										{
											break;
										}
										else if(board[y_adj][x_decre] 
												== player_token)
										{
											for(x_decre = (x_decre + 1); 
												x_decre < x_current; 
												x_decre++)
											{
												board[y_adj][x_decre] 
												= player_token;
												captured_pieces += 1;
											}
											break;
										}
										else
										{
											continue;
										}
									}
								}
								break;
					case NORTH_EAST:/*Gets the coordinate for the*/
									/*adjacent NORTH_EAST tile */
									/*Decrements the y-axis*/
									y_adj = y_current - 1;
									/*Increments the x-axis*/
									x_adj = x_current + 1;
									/*Refer to NORTH case for logic*/
									if(board[y_adj][x_adj] != BLANK && 
									   board[y_adj][x_adj] != player_token)
									{
										for(x_incre = (x_current + 2), 
											y_decre = (y_current - 2); 
											x_incre < BOARD_WIDTH && 
											y_decre >= 0; 
											x_incre++, 
											y_decre--)
										{
											if(board[y_decre][x_incre] 
											   == BLANK)
											{
												break;
											}
											else if(board[y_decre][x_incre] 
												    == player_token)
											{
												for(x_incre = (x_incre - 1), 
													y_decre = (y_decre + 1); 
													x_incre > x_current && 
													y_decre < y_current; 
													x_incre--, y_decre++)
												{
													board[y_decre][x_incre] 
													= player_token;
													captured_pieces += 1;
												}
												break;
											}
											else
											{
												continue;
											}
										}
									}
									break;
					case NORTH_WEST:/*Gets the coordinate for the*/
									/*adjacent NORTH_WEST tile */
									/*Decrements the y-axis*/
									y_adj = y_current - 1;
									/*Decrements the x-axis*/
									x_adj = x_current - 1;
									/*Refer to NORTH case for logic*/
									if(board[y_adj][x_adj] != BLANK && 
									   board[y_adj][x_adj] != player_token)
									{
										for(x_decre = (x_current - 2), 
											y_decre = (y_current - 2); 
											x_decre >= 0 && y_decre >= 0; 
											x_decre--, 
											y_decre--)
										{
											if(board[y_decre][x_decre] 
											   == BLANK)
											{
												break;
											}
											else if(board[y_decre][x_decre] 
												    == player_token)
											{
												for(x_decre = (x_decre + 1), 
													y_decre = (y_decre + 1); 
													x_decre < x_current && 
													y_decre < y_current; 
													x_decre++, 
													y_decre++)
												{
													board[y_decre][x_decre] 
													= player_token;
													captured_pieces += 1;
												}
												break;
											}
											else
											{
												continue;
											}
										}
									}
									break;
					case SOUTH_EAST:/*Gets the coordinate for the*/
									/*adjacent SOUTH_EAST tile */
									/*Increments the y-axis*/
									y_adj = y_current + 1;
									/*Increments the x-axis*/
									x_adj = x_current + 1;
									/*Refer to NORTH case for logic*/
									if(board[y_adj][x_adj] != BLANK && 
									   board[y_adj][x_adj] != player_token)
									{
										for(x_incre = (x_current + 2), 
											y_incre = (y_current + 2); 
											x_incre < BOARD_WIDTH && 
											y_incre < BOARD_HEIGHT; 
											x_incre++, 
											y_incre++)
										{
											if(board[y_incre][x_incre] 
											   == BLANK)
											{
												break;
											}
											else if(board[y_incre][x_incre] 
												    == player_token)
											{
												for(x_incre = (x_incre - 1), 
													y_incre = (y_incre - 1); 
													x_incre > x_current && 
													y_incre > y_current; 
													x_incre--, 
													y_incre--)
												{
													board[y_incre][x_incre] 
													= player_token;
													captured_pieces += 1;
												}
												break;
											}
											else
											{
												continue;
											}
										}
									}
									break;
					case SOUTH_WEST:/*Gets the coordinate for the*/
									/*adjacent SOUTH_WEST tile */
									/*Increments the y-axis*/
									y_adj = y_current + 1;
									/*Decrements the x-axis*/
									x_adj = x_current - 1;
									/*Refer to NORTH case for logic*/
									if(board[y_adj][x_adj] != BLANK && 
									   board[y_adj][x_adj] != player_token)
									{
										for(x_decre = (x_current - 2), 
											y_incre = (y_current + 2); 
											x_decre >= 0 && 
											y_incre < BOARD_HEIGHT; 
											x_decre--, 
											y_incre++)
										{
											if(board[y_incre][x_decre] 
											   == BLANK)
											{
												break;
											}
											else if(board[y_incre][x_decre] 
												    == player_token)
											{
												for(x_decre = (x_decre + 1), 
													y_incre = (y_incre - 1); 
													x_decre < x_current && 
													y_incre > y_current; 
													x_decre++, 
													y_incre--)
												{
													board[y_incre][x_decre] 
													= player_token;
													captured_pieces += 1;
												}
												break;
											}
											else
											{
												continue;
											}
										}
									}
									break;
				}
			}
			/*Whenever there are captured pieces*/
			if(captured_pieces > 0)
			{
				/*Sets the player input tile to be the player token*/
				board[y_current][x_current] = player_token;
				successful_move = TRUE;
			}
			else
			{
				printf("Coordinates entered is invalid.\n");
				printf("None of the adjacent pieces can be captured.\n\n");
				successful_move = FALSE;
			}
		}
		else
		{
			printf("Coordinates entered is invalid.\n");
			printf("The entered cell (%d,%d) is already occupied.\n\n", x, y);
			successful_move = FALSE;
		}
    }
    else
    {
    	printf("An error has occurred. Either the\n");
    	printf("',' was not used to separate the x and y values or\n");
    	printf("coordinates entered is not within the bounds of the board.\n");
    	printf("The values need to be within 1 and %d.\n\n", BOARD_HEIGHT);
    	successful_move = FALSE;
    }
    return successful_move;
}

/**
 * simply count up how many locations contain the player_token 
 * specified on the game_board.
 **/
unsigned game_score(game_board board, enum cell player_token)
{
	unsigned int score = 0;
	int row = 0;
	int column = 0;
	/*Iterates through the board row*/
	for(row = 0; row < BOARD_HEIGHT; row++)
	{
		/*Iterates through the board column*/
		for(column = 0; column < BOARD_WIDTH; column++)
		{
			/*Checks if the board's cell houses the player token*/
			if(board[row][column] == player_token)
			{
				/*Increments the score*/
				score += 1;
			}
		}
	}
	/*returns the score*/
	return score;
}

/**
 * swap the two player pointers passed in so that first points to the player
 * pointer that originally contained the second player and vice versa.
 **/
void swap_players(struct player ** first, struct player ** second)
{
	struct player *temp = *second;
	*second = *first;
	*first = temp;
}
