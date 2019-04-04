#ifdef __cplusplus
extern "C"
{
#endif

#ifndef __GUI_H__
#define __GUI_H__

#include <stdio.h>

/* safe printf macro */
#define DRAW(str) do { printf("%s", str); } while(0)

/* single box characters */
#define BOX_TLC_S   "┌"
#define BOX_TRC_S   "┐"
#define BOX_BLC_S   "└"
#define BOX_BRC_S   "┘"
#define BOX_VER_S   "│"
#define BOX_HOR_S   "─"
#define BOX_LT_S    "┤"
#define BOX_RT_S    "├"
#define BOX_DT_S    "┬"
#define BOX_UT_S    "┴"
#define BOX_MT_S    "┼"

/* double box characters */
#define BOX_TLC_D   "╔"
#define BOX_TRC_D   "╗"
#define BOX_BLC_D   "╚"
#define BOX_BRC_D   "╝"
#define BOX_VER_D   "║"
#define BOX_HOR_D   "═"
#define BOX_LT_D    "╣"
#define BOX_RT_D    "╠"
#define BOX_DT_D    "╦"
#define BOX_UT_D    "╩"
#define BOX_MT_D    "╬"

/* box character fallback */
#define BOX_COR_F   "="
#define BOX_VER_F   "|"
#define BOX_HOR_F   "="

/* gradient characters */
#define GRAD_L      "░"
#define GRAD_M      "▒"
#define GRAD_H      "▓"

/* ANSI text attributes */
typedef enum
{
    OFF     = 0,
    BOLD    = 1,
    UNDRSCR = 4,
    BLINK   = 5,
    REV_VID = 7,
    CONCEAL = 8
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

/* exit handler */

void gui_cleanup(void);     /* reset all */
void cleanup_wrap(int);

/* functional */

void gui_init(void);

void set_cursor(int,        /* cursor line position */
                int);       /* cursor column position */

void attr_none(void);
void attr(ATTR);            /* text attribute */
void fore(FORE);            /* ISO 6429 color code */
void back(BACK);            /* ISO 6429 color code */

/* terminal interface */

/* set the terminal to standard mode */
void std_mode(void);

/* set the terminal to raw mode */
void raw_mode(void);

/* get a character in raw mode */
int getch_raw();

/* bell */
void bell(void);

/* rendering / UI */

/* clear the terminal */
void clear(void);

void heatmap(int**,         /* data */
             int,           /* rows */
             int,           /* cols */
             int,           /* top left row index of box */
             int);          /* top left col index of box */

/* returns selected option index */
int optionbox(const char**, /* options array */
              int,          /* top left row index of box */
              int);         /* top left column index of box */

/* get an integer from user */
int query_int(int,          /* top left row index of box */
              int,          /* top left column index of box */
              char*);       /* prompt */

/* get an integer from user */
double query_double(int,    /* top left row index of box */
                    int,    /* top left column index of box */
                    char*); /* prompt */

/* fill a space with a gradient */
void grad_fill(int,         /* top left corner line */ 
               int,         /* tope left corner column */
               int,         /* int width (overall) */
               int,         /* int height (overall) */
               const char); /* mode (l - light, m - medium, h - heavy) */

/* draw a box with specified character set */
void draw_box(int,          /* top left corner line */
              int,          /* top left corner column */
              int,          /* int width (inside box) */
              int,          /* int height (inside box) */
              const char);  /* mode (s - single, d - double, f - fallback) */

/* mode specific box drawing */

static void draw_box_s(int,
                       int,
                       int,
                       int);


static void draw_box_d(int,
                       int,
                       int,
                       int);


static void draw_box_f(int,
                       int,
                       int,
                       int);
#endif

#ifdef __cplusplus
}
#endif
