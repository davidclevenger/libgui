#include <stdio.h>
#include <unistd.h>
#include "core.h"

int main()
{
	char str[30];
	GUI gui;

	/* initialize the struct */
	GUI_init(&gui);

	/* set the box color */
	text_fore(&gui, RED_FORE);

	/* create a prompt */
	draw_box(4,4, 20, 1);
	cur_pos(5, 5);

	/* set the prompt color */
	text_fore(&gui, BLU_FORE);
	printf("Name: ");

	scanf("%s", str);
	clear();

	/* remove text attributes */
	attr_none(&gui);
	
	printf("Hello, %s", str);
	fflush(stdout);
	sleep(3);

}
