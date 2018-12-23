#ifndef __C4_H__
#define __C4_H__

#define BOARD_ROW 6
#define BOARD_COL 7

/* game pieces */
#define UNUSED 'O'
#define RED 'R'
#define BLK 'B'

/* game logic */
#define COM 0
#define HUM 1

typedef struct
{
	char board[BOARD_ROW][BOARD_COL];
} Game;

int play(Game*);
int foundWinner(Game*, int*);
int pickSpot(Game*, int);

#endif
