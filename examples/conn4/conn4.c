/*	Simple connect (4 colored disks) implementation.
* 	
*	*checks only vertical and horizontal connections.
*	*human goes first (red), computer second (black).
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

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

	return 0; /* winner not found */
}

void pickSpot(Game* game, int player)
{
	int i, j;
	int choice = 0;
	char s;
	int done = 0;

	if( player == HUM )
	{
		raw_mode();

		while( !done && read(STDIN_FILENO, &s, 1) == 1 )
		{
			if( s == DOWN )
			{
				if( game->board[0][game->choice] == UNUSED )
				{
					/* drop */
					for(i = BOARD_ROW-1; i >= 0; i--)
					{
						if( game->board[i][game->choice] == UNUSED )
						{
							game->board[i][game->choice] = R;
							done = 1;
							break;
						}
					}
				}
			}
			else if( s == LEFT && game->choice > 0)
			{
				--(game->choice);
				update(game);

			}
			else if( s == RIGHT && game->choice < BOARD_COL-1)
			{
				++(game->choice);
				update(game);
			}
			else if( s == 'q' )
			{
				exit(0);
			}
		}

		std_mode();
	}
	else /* computer's pick */
	{
		/* find first available column */
		for(i = 0; i < BOARD_COL; i++)
		{
			if( game->board[0][i] == UNUSED)
			{
				break;
			}
		}

		/* drop */
		for( j = BOARD_ROW - 1; j >= 0; j--)
		{
			if( game->board[j][i] == UNUSED )
			{
				game->board[j][i] = B;
				break;
			}
		}
	}
}

int play(Game* game)
{
	int i, j;
	int winner;
	
	game->turn = HUM;
	game->choice = 0;

	gui_init();

	/* fill in choice buffer */
	for(i = 0; i < BOARD_COL; i++)
	{
		game->choicebuf[i] = 'X';
	}

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
		if( game->turn == HUM )
		{
			pickSpot(game, HUM);
			game->turn = COM;
		}
		else /* computer's turn */
		{
			pickSpot(game, COM);
			game->turn = HUM;
		}

		update(game);
	}

	return winner;
}

void update(Game* game)
{
	int i, j;
	
	clear();
	cur_pos(1,0);

	if(game->turn == HUM)
	{
		for(i = 0; i < BOARD_COL; i++)
		{
			if( i != game->choice )
			{
				printf("X");
			}
			else /* is choice */
			{
				fore(RED);
				printf("%c", R);
				attr_none();
			}
		}
		printf("\n");

		attr_none();
	}
	else
	{
		for(i = 0; i < BOARD_COL; i++)
		{
			printf("X");
		}
		printf("\n");
	}

	for(i = 0; i < BOARD_ROW; i++)
	{
		for(j = 0; j < BOARD_COL; j++)
		{
			switch( game->board[i][j] )
			{
				case UNUSED:
					attr_none();
					printf("%c", UNUSED);
					break;

				case R:
					fore(RED);
					printf("%c", R);
					break;

				case B:
					fore(BLK);
					printf("%c", B);
					break;
			}
		}
		printf("\n");
	}
}

int main()
{
	int win;
	Game game;

	win = play(&game);
	clear();

	/* alert player */
	bell();

	if( win == HUM )
	{
		printf("You won!\n");
		sleep(4);
	}
	else
	{
		printf("You lost!\n");
		sleep(4);
	}
}
