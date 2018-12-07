#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "core.h"

/* exit handler */

void
gui_cleanup(void)
{
	/* clear all attributes */
	printf("\x1B[0m");
	clear();

	/* reset cursor position */
	printf("\n\x1B[0;0H");
	clear();
}

void
cleanup_wrap(int status)
{
	gui_cleanup();
	exit(status);
}

/* functional */

void
gui_init()
{
	/* register cleanup handler */
	if( atexit(gui_cleanup) != 0 )
	{
		fprintf(stderr, "Init failure\n");
		exit(1);
	}

	signal(SIGINT, cleanup_wrap);
	signal(SIGTERM, cleanup_wrap);

	clear();
	cur_pos(0,0);
}

void
cur_pos(int x, int y)
{
	if( x < 0 || y < 0 ) return;

	printf("\x1B[%d;%dH", x, y);
	fflush(stdout);
}

void
attr_none()
{
	printf("\x1B[0m");
}

void
attr(ATTR attr)
{
	if( attr < 0 || attr > 8 ) return;

	printf("\x1B[%dm", attr);
}

void
fore(FORE fore)
{
	if( fore < 30 || fore > 37 ) return;

	printf("\x1B[%dm", fore);
}

void
back(BACK back)
{
	if( back < 40 || back > 47 ) return;

	printf("\x1B[%dm", back);
}

/* rendering */

void
clear()
{
	printf("\x1B[2J");
	cur_pos(0, 0);
}

void
grad_fill(int x, int y, int w, int h, const char mode)
{
	int i;
	int j;

	char* pick = GRAD_M; /* default fill */
	
	switch(mode)
	{
		case 'l':
			pick = GRAD_L; 
			break;

		case 'm':
			pick = GRAD_M;
			break;

		case 'h':
			pick = GRAD_H;
			break;
	}

	for(i = 0; i < h; i++)
	{
		cur_pos(x + i, y);
		for(j = 0; j < w; j++)
		{
			DRAW(pick);
		}
	}

	fflush(stdout);
}

void
draw_box(int x, int y, int w, int h, const char mode)
{
	/* set the drawing location */
	cur_pos(x, y);

	switch(mode)
	{
		case 's': /* single box */
			draw_box_s(x, y, w, h);
			break;

		case 'd': /* double box */
			draw_box_d(x, y, w, h);
			break;

		case 'f': /* fallback box */
			draw_box_f(x, y, w, h);
			break;

		default: /* fallback box */
			draw_box_f(x, y, w, h);
			break;
	}

	/* force write */
	fflush(stdout);
}

static void
draw_box_s(int x, int y, int w, int h)
{
	int i;
	int j;

	/* first layer */
	DRAW(BOX_TLC_S);
	for(i = 0; i < w; i++)
	{
		DRAW(BOX_HOR_S);
	}
	DRAW(BOX_TRC_S);

	/* middle layers */
	for(j = 0; j < h; j++)
	{
		cur_pos(x+j+1, y);
		DRAW(BOX_VER_S);
		for(i = 0; i < w; i++)
		{
			printf(" ");
		}
		DRAW(BOX_VER_S);
	}

	cur_pos(x+j+1, y);
	
	/* last layer */
	DRAW(BOX_BLC_S);
	for(i = 0; i < w; i++)
	{
		DRAW(BOX_HOR_S);
	}
	DRAW(BOX_BRC_S);
}

static void
draw_box_d(int x, int y, int w, int h)
{
	int i;
	int j;

	/* first layer */
	DRAW(BOX_TLC_D);
	for(i = 0; i < w; i++)
	{
		DRAW(BOX_HOR_D);
	}
	DRAW(BOX_TRC_D);

	/* middle layers */
	for(j = 0; j < h; j++)
	{
		cur_pos(x+j+1, y);
		DRAW(BOX_VER_D);
		for(i = 0; i < w; i++)
		{
			printf(" ");
		}
		DRAW(BOX_VER_D);
	}

	cur_pos(x+j+1, y);
	
	/* last layer */
	DRAW(BOX_BLC_D);
	for(i = 0; i < w; i++)
	{
		DRAW(BOX_HOR_D);
	}
	DRAW(BOX_BRC_D);
}

static void
draw_box_f(int x, int y, int w, int h)
{
	int i;
	int j;

	/* first layer */
	DRAW(BOX_COR_F);
	for(i = 0; i < w; i++)
	{
		DRAW(BOX_HOR_F);
	}
	DRAW(BOX_COR_F);

	/* middle layer(s) */
	for(j = 0; j < h; j++)
	{

		cur_pos(x+j+1, y);
		DRAW(BOX_VER_F);
		for(i = 0; i < w; i++)
		{
			printf(" ");
		}
		DRAW(BOX_VER_F);
	}

	cur_pos(x+j+1, y);

	/* last layer */
	DRAW(BOX_COR_F);
	for(i = 0; i < w; i++)
	{
		DRAW(BOX_HOR_F);
	}
	DRAW(BOX_COR_F);
}
