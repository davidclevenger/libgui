#ifdef __cplusplus
extern "C"
{
#endif

#ifndef __CORE_H__
#define __CORE_H__

#include <stdio.h>

/* BOX characters */

#define BOX_COR " "
#define BOX_HOR "-"
#define BOX_VER "|"

/* ANSI text attributes */
typedef enum
{
	OFF		= 0,
	BOLD	= 1,
	UNDRSCR	= 4,
	BLINK	= 5,
	REV_VID	= 7,
	CONCEAL	= 8
} ATTR;

/* ISO 6429 ANSI color sequences */
typedef enum
{
	NON = -1,
	BLK = 30,
	RED = 31,
	GRN = 32,
	YLW = 33,
	BLU = 34,
	MAG = 35,
	CYN = 36,
	WHT = 37
} FORE;

typedef enum
{
	NON_BACK = -1,
	BLK_BACK = 40,
	RED_BACK = 41,
	GRN_BACK = 42,
	YLW_BACK = 43,
	BLU_BACK = 44,
	MAG_BACK = 45,
	CYN_BACK = 46,
	WHT_BACK = 47
} BACK;

typedef struct
{
	int curX;				/* line position of cursor */
	int curY;				/* column position of cursor */
	ATTR attr;				/* text attribute */
	FORE fore;				/* foreground text color */
	BACK back;				/* background text color */
} GUI;

/* exit handler */

void GUI_cleanup(void);		/* reset all */

/* functional */

void GUI_init(GUI*);		/* GUI struct */

void cur_pos(int,			/* cursor line position */
			 int);			/* cursor column position */

void attr_none(GUI*);		/* GUI struct */

void text_attr(GUI*,		/* GUI struct */
			   ATTR);		/* text attribute */

void text_fore(GUI*,		/* GUI struct */
			   FORE);		/* ISO 6429 color code */

void text_back(GUI*,		/* GUI struct */
			   BACK);		/* ISO 6429 color code */

/* rendering */

void clear();				/* clear the terminal */

void draw_box(int,			/* top left corner line */
			  int,			/* top left corner column */
			  int,			/* int width (inside box) */
			  int);			/* int height (inside box) */

#endif

#ifdef __cplusplus
}
#endif
