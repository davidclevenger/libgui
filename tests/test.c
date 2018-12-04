#include <stdio.h> 	/* printf */
#include <unistd.h>	/* sleep */

#include "core.h"

int main()
{
	GUI gui;

	/* initialize gui and clear screen */
	GUI_init(&gui);
	clear();

	/* test each foreground color */
	text_fore(&gui, BLK);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	text_fore(&gui, RED);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	text_fore(&gui, GRN);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	text_fore(&gui, BLU);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	text_fore(&gui, MAG);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	text_fore(&gui, CYN);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	text_fore(&gui, WHT);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	/* remove attributes */
	attr_none(&gui);

	/* test each backgroud color */
	text_back(&gui, BLK_BACK);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	text_back(&gui, RED_BACK);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	text_back(&gui, GRN_BACK);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	text_back(&gui, YLW_BACK);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	text_back(&gui, BLU_BACK);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	text_back(&gui, MAG_BACK);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	text_back(&gui, CYN_BACK);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	text_back(&gui, WHT_BACK);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	/* reset attributes */
	attr_none(&gui);
	clear();

	/* test each text attribute */
	text_attr(&gui, BOLD);
	printf("bold\n");
	sleep(1);
	attr_none(&gui);

	text_attr(&gui, UNDRSCR);
	printf("underscore\n");
	sleep(1);
	attr_none(&gui);
	
	text_attr(&gui, BLINK);
	printf("blink\n");
	sleep(3);
	attr_none(&gui);

	text_attr(&gui, REV_VID);
	printf("reverse video\n");
	sleep(1);
	attr_none(&gui);

	text_attr(&gui, CONCEAL);
	text_back(&gui, RED_BACK); /* show that text is concealed */
	printf("conceal\n");
	sleep(1);
	attr_none(&gui);

	clear();

	/* single box */

	text_fore(&gui, BLU);

	draw_box(1, 0, 4, 4, 's');
	sleep(1);

	/* double box */

	draw_box(1, 0, 4, 4, 'd');
	sleep(1);

	clear();

	/* gradients */
	grad_fill(1, 0, 4, 4, 'l');
	sleep(1);

	grad_fill(1, 0, 4, 4, 'm');
	sleep(1);

	grad_fill(1, 0, 4, 4, 'h');
	sleep(1);
}
