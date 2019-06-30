/**
 * for display
 * 
 * last update: 2019-06-28
 */

#include <ncurses.h>
#include <stdlib.h>

#define IMG_ROWS 28
#define IMG_COLS 28

void print_img_ans(WINDOW *win, char *img, int ans);

int main(int argc, char *argv[])
{
    char *img;
    int ans;
    WINDOW *win;

    /* Initialize curses */
    initscr();
    clear();
    noecho();
    cbreak();
    //mvprintw(23, 1, "It just a sring");
    refresh();

    /* Load data */
    img = (char *)calloc(IMG_ROWS * IMG_COLS, sizeof(char));

    /* Do something */
    ans = 7;

    /* Draw img and ans*/
    win = newwin(1 + IMG_ROWS + 1,
                 1 + IMG_COLS + 2 + 2 + 2 + 1,
                 0,
                 0);

    print_img_ans(win, img, ans);

    /* Wait */
    getch();

    /* Free */
    free(img);
    endwin();

    return 0;
}

/**
 * draw "img = ans"
 */
void print_img_ans(WINDOW *win, char *img, int ans)
{
    char *p = img;
    int row, col;

    box(win, 0, 0);

    for (row = 0; row < IMG_ROWS; row++)
    {
        wmove(win, row + 1, 1);
       for (col = 0; col < IMG_COLS; col++)
        {
            if (*p == '0')
                waddch(win, ACS_LANTERN);
            else
                waddch(win, ACS_CKBOARD);
            p++;
        }
    }

    wmove (win, IMG_ROWS / 2, 1 + IMG_COLS + 1);
    wprintw(win, " = ");
    waddch(win, '0' + ans);
    wrefresh(win);
}
