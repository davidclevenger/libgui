#ifndef __C4_H__
#define __C4_H__

#define BOARD_ROW 6
#define BOARD_COL 7

/* game pieces */
#define UNUSED 'O'
#define R 'R'
#define B 'B'

/* game logic */
#define COM 0
#define HUM 1

/* arrow keys */
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'

typedef struct
{
	char choicebuf[BOARD_COL];
	char board[BOARD_ROW][BOARD_COL];
	int choice;
	int turn;
} Game;

int play(Game*);
int foundWinner(Game*, int*);
void pickSpot(Game*, int);
void update(Game*);

#endif
