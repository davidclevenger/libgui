#include <stdio.h> 	/* printf */
#include <unistd.h>	/* sleep */
#include <stdlib.h> /* NULL */

#include "gui.h"

int main()
{
	/* initialize and clear screen */
	gui_init();
	clear();

	/* test each foreground color */
	fore(BLK);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	fore(RED);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	fore(GRN);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	fore(BLU);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	fore(MAG);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	fore(CYN);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	fore(WHT);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	/* remove attributes */
	attr_none();

	/* test each backgroud color */
	back(BLK_BACK);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	back(RED_BACK);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	back(GRN_BACK);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	back(YLW_BACK);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	back(BLU_BACK);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	back(MAG_BACK);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	back(CYN_BACK);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	back(WHT_BACK);
	draw_box(1, 0, 4, 4, 'f');
	sleep(1);

	/* reset attributes */
	attr_none();
	clear();

	/* test each text attribute */
	attr(BOLD);
	printf("bold\n");
	sleep(1);
	attr_none();

	attr(UNDRSCR);
	printf("underscore\n");
	sleep(1);
	attr_none();
	
	attr(BLINK);
	printf("blink\n");
	sleep(3);
	attr_none();

	attr(REV_VID);
	printf("reverse video\n");
	sleep(1);
	attr_none();

	attr(CONCEAL);
	back(RED_BACK); /* show that text is concealed */
	printf("conceal\n");
	sleep(1);
	attr_none();

	clear();

	/* single box */

	fore(BLU);

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

    const char* options[] = {
        "GUIS",
        "ARE",
        "FUN!",
		NULL
    };

	int choice = optionbox(options, 1, 1);

    printf("You chose: %d %s\n", choice, options[choice]);
	sleep(2);

}
