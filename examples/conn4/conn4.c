/*	Simple connect (4 colored disks) implementation.
* 	
*	*checks only vertical and horizontal connections.
*	*human goes first (red), computer second (black).
*/

#include <stdlib.h>
#include "gui.h"
#include "conn4.h"

int foundWinner(Game* game, int* winner)
{
	int i, j;

	/* brute force.. */

	/* horizontal */
	for(i = 0; i < BOARD_ROW; i++)
	{
		for(j = 0; j < BOARD_COL - 3; j++)
		{
			if( game->board[i][j] == 'R' &&
				game->board[i][j+1] == 'R' &&
				game->board[i][j+2] == 'R' &&
				game->board[i][j+3] == 'R' )
			{
				*winner = HUM;
				return 1;
			}
			else if( game->board[i][j] == 'B' &&
					 game->board[i][j+1] == 'B' &&
					 game->board[i][j+2] == 'B' &&
					 game->board[i][j+3] == 'B' )
			{
				*winner = COM;
				return 1;
			}
		}
	}

	/* vertical */
	for(i = 0; i < BOARD_ROW - 3; i++)
	{
		for(j = 0; j < BOARD_COL; j++)
		{
			if( game->board[i][j] == 'R' &&
				game->board[i+1][j] == 'R' &&
				game->board[i+2][j] == 'R' &&
				game->board[i+3][j] == 'R' )
			{
				*winner = HUM;
				return 1;
			}
			else if( game->board[i][j] == 'B' &&
					 game->board[i+1][j] == 'B' &&
					 game->board[i+2][j] == 'B' &&
					 game->board[i+3][j] == 'B' )
			{
				*winner = COM;
				return 1;
			}
		}
	}

	return 0 /* winner not found */
}

void pickSpot(Game* game, int player)
{
	if( player == HUM )
	{

	}
	else /* computer's pick */
	{
		
	}
}

int play(Game* game)
{
	int i, j;
	int winner;
	int turn = HUM;

	/* fill in board */
	for(i = 0; i < BOARD_ROW; i++)
	{
		for(j = 0; j < BOARD_COL; j++)
		{
			game->board[i][j] = UNUSED;
		}
	}

	/* begin game */
	update(game);

	while( !foundWinner(game, &winner) )
	{
		if( turn == HUM )
		{
			pickSpot(game, HUM);
			turn = COM;
		}
		else /* computer's turn */
		{
			pickSpot(game, COM);
			turn = HUM;
		}

		update(game);
	}

	return winner;
}

int main()
{
	int win;
	Game* game;

	win = play(game);

	if( win == HUM )
	{
		printf("You won!\n");
	}
	else
	{
		printf("You lost!\n");
	}
}
