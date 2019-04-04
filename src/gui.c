#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <limits.h>
#include <string.h>

#include "gui.h"

struct termios preserve;

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
    std_mode();
    gui_cleanup();
    exit(status);
}

/* functional */

void
gui_init(void)
{
    /* register cleanup handlers */
    if( atexit(std_mode) != 0 )
    {
        fprintf(stderr, "Init failure\n");
        exit(1);
    }

    if( atexit(gui_cleanup) != 0 )
    {
        fprintf(stderr, "Init failure\n");
        exit(1);
    }

    signal(SIGINT, cleanup_wrap);
    signal(SIGTERM, cleanup_wrap);

    /* preserve terminal configuration */
    std_mode();

    /* clear screen and position cursor */
    clear();
    set_cursor(0,0);
}

void
set_cursor(int x, int y)
{
    if( x < 0 || y < 0 ) return;

    printf("\x1B[%d;%dH", x, y);
    fflush(stdout);
}

void
attr_none(void)
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

/* terminal interface */

void
std_mode(void)
{
    static int called = 0;

    if( !called )
    {
        tcgetattr(STDIN_FILENO, &preserve);
    }

    /* ensure terminal configuration is preserved */
    called = 1;

    /* restore the original configuration */
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &preserve);
}

void
raw_mode(void)
{
    struct termios term;

    /* get current state and set raw flags */
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

int
getch_raw()
{
    char c;
    raw_mode();
    c = getchar();
    std_mode();
    return c;
}

/* bell */

void
bell(void)
{
    char c = 7; /* bell character */
    printf("%c", c);
    fflush(stdout);
}

/* rendering */

void
clear(void)
{
    printf("\x1B[2J");
    set_cursor(0, 0);
}

void
heatmap(int** data, int r, int c, int x, int y)
{
    int i, j, mid_l, mid_u;
    int min = INT_MAX;
    int max = INT_MIN;

    set_cursor(x,0);

    for( i = 0; i < r; i++)
    {
        for( j = 0; j < c; j++)
        {
            if( data[i][j] > max )
            {
                max = data[i][j];
            }

            else if( data[i][j] < min )
            {
                min = data[i][j];
            }
        }
    }

    mid_l = ((( max + min ) / 2 ) + min ) / 2;
    mid_u = ((( max + min ) / 2 ) + max ) / 2;

    for( i = 0; i < r; i++)
    {
        for( j = 0; j < c; j++)
        {
            if( data[i][j] > mid_u )
            {
                fore(GRN);
                printf(GRAD_M);
            }
            else if( data[i][j] > mid_l )
            {
                fore(YLW);
                printf(GRAD_M);
            }
            else /* data[i][j] <= mid_l */
            {
                fore(RED);
                printf(GRAD_M);
            }
        }
		printf("\n");
    }

    fflush(stdout);
}

int
optionbox(const char** options, int x, int y)
{
    int i, len;
    unsigned int max_len = 0;
    int choice;
    char c;

	attr_none();

    len = 0;
    while( options[len] )
    {
        if( strlen(options[len]) > max_len)
        {
            max_len = strlen(options[len]);
        }
		++len;
    }

    draw_box(x, y, max_len + 5, len, 'd');
    set_cursor(++x, ++y);

    c = '0';
    do
    {
		
		switch( c )
		{
			case 'w':
				if( choice > 0 )
					--choice;
				break;

			case 'W':
				choice = 0;
				break;

			case 's':
				if( choice < len - 1)
					++choice;
				break;

			case 'S':
				choice = len - 1;
				break;
		}

        for(i = 0; i < len; ++i)
        {
            set_cursor(x+i, y);
            if( i == choice)
            {
                attr(REV_VID);
				fore(RED);
            }
            else
            {
                attr(OFF);
            }
            printf("%2d: %s", i+1, options[i]);
        }
    } while( (c = getch_raw()) != '\n');

	attr_none();
    return choice;
}

int query_int(int x, int y, char* prompt)
{
    char raw[20];
    int height = 1, width;
    if( prompt == NULL )
    {
        width = 20;
    }
    else
    {
        width = strlen(prompt) + 20;
    }

    draw_box(x,y, width, height, 'd');
    set_cursor(x+1, y+1);
    if( prompt )
    {
        printf("%s", prompt);
    }

    fgets(raw, 20, stdin);
    clear();
    return atoi(raw);

}

double query_double(int x, int y, char* prompt)
{
    
    char raw[20];
    int height = 1, width;
    if( prompt == NULL )
    {
        width = 10;
    }
    else
    {
        width = strlen(prompt) + 1 + 10;
    }

    draw_box(x,y, width, height, 'd');
    set_cursor(x+1, y+1);
    if( prompt )
    {
        printf("%s ", prompt);
    }

    fgets(raw, 20, stdin);
    clear();
    return atof(raw);
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
        set_cursor(x + i, y);
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
    set_cursor(x, y);

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
        set_cursor(x+j+1, y);
        DRAW(BOX_VER_S);
        for(i = 0; i < w; i++)
        {
            printf(" ");
        }
        DRAW(BOX_VER_S);
    }

    set_cursor(x+j+1, y);
    
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
        set_cursor(x+j+1, y);
        DRAW(BOX_VER_D);
        for(i = 0; i < w; i++)
        {
            printf(" ");
        }
        DRAW(BOX_VER_D);
    }

    set_cursor(x+j+1, y);
    
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

        set_cursor(x+j+1, y);
        DRAW(BOX_VER_F);
        for(i = 0; i < w; i++)
        {
            printf(" ");
        }
        DRAW(BOX_VER_F);
    }

    set_cursor(x+j+1, y);

    /* last layer */
    DRAW(BOX_COR_F);
    for(i = 0; i < w; i++)
    {
        DRAW(BOX_HOR_F);
    }
    DRAW(BOX_COR_F);
}

