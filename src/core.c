#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "core.h"

/* exit handler */

void
GUI_cleanup(void)
{
	/* clear all attributes */
	printf("\x1B[0m");
	clear();

	/* reset cursor position */
	printf("\n\x1B[0;0H");
	clear();
}

/* functional */

void
GUI_init(GUI* gui)
{
	/* register cleanup handler */
	if( atexit(GUI_cleanup) != 0 )
	{
		fprintf(stderr, "Init failure\n");
		exit(1);
	}

	clear();
	cur_pos(0,0);

	gui->curX = 0;
	gui->curY = 0;
	gui->fore = -1;
	gui->back = -1;
}

void
cur_pos(int x, int y)
{
	if( x < 0 || y < 0 ) return;

	printf("\x1B[%d;%dH", x, y);
}

void
attr_none(GUI* gui)
{
	printf("\x1B[0m");
}

void
text_attr(GUI* gui, int attr)
{
	if( attr < 0 || attr > 8 ) return;

	printf("\x1B[%dm", attr);
}

void
text_fore(GUI* gui, int fore)
{
	if( fore < 30 || fore > 37 ) return;

	printf("\x1B[%dm", fore);
}

void
text_back(GUI* gui, int back)
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
draw_box(int x, int y, int w, int h)
{
	int i;
	int j;
	char buf[1024];

	/* set the cursor position */
	cur_pos(x, y);

	/* first layer */
	printf(BOX_COR);
	for(i = 0; i < w; i++)
	{
		printf(BOX_HOR);
	}
	printf(BOX_COR);

	/* middle layer(s) */
	for(j = 0; j < h; j++)
	{
	
		cur_pos(x+j+1, y);
		printf(BOX_VER);
		for(i = 0; i < w; i++)
		{
			printf(" ");
		}
		printf(BOX_VER);
	}

	cur_pos(x+j+1, y);

	/* last layer */
	printf(BOX_COR);
	for(i = 0; i < w; i++)
	{
		printf(BOX_HOR);
	}
	printf(BOX_COR);
}
