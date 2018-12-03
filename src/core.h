#ifndef __CORE_H__
#define __CORE_H__

#include <stdio.h>

/* ANSI text attributes */

#define OFF		0
#define BOLD	1
#define UNDRSCR	4
#define BLINK	5
#define REV_VID	7
#define CONCEAL	8

/* ISO 6429 ANSI color sequences */

#define BLK_FORE 30
#define RED_FORE 31
#define GRN_FORE 32
#define YLW_FORE 33
#define BLU_FORE 34
#define MAG_FORE 35
#define CYN_FORE 36
#define WHT_FORE 37

#define BLK_BACK 40
#define RED_BACK 41
#define GRN_BACK 42
#define YLW_BACK 43
#define BLU_BACK 44
#define MAG_BACK 45
#define CYN_BACK 46
#define WHT_BACK 47

/* BOX characters */

#define BOX_COR " "
#define BOX_HOR "="
#define BOX_VER "|"


typedef struct
{
	int curX;				/* line position of cursor */
	int curY;				/* column position of cursor */
	int fore;				/* foreground text color */
	int back;				/* background text color */
} GUI;

/* exit handler */

void GUI_cleanup(void);		/* reset all */

/* functional */

void GUI_init(GUI*);		/* GUI struct */

void cur_pos(int,			/* cursor line position */
			 int);			/* cursor column position */

void attr_none(GUI*);		/* GUI struct */

void text_attr(GUI*,		/* GUI struct */
			   int);		/* text attribute */

void text_fore(GUI*,		/* GUI struct */
			   int);		/* ISO 6429 color code */

void text_back(GUI*,		/* GUI struct */
			   int);		/* ISO 6429 color code */

/* rendering */

void clear();				/* clear the terminal */

void draw_box(int,			/* top left corner line */
			  int,			/* top left corner column */
			  int,			/* int width (inside box) */
			  int);			/* int height (inside box) */

#endif
