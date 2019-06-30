/**
 * for display
 * 
 * last update: 2019-06-30
 */

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

#include "dataset.h"
#include "model_1.h"

#define IMG_ROWS 28
#define IMG_COLS 28

void print_img_ans(WINDOW *win, const unsigned char *img, int ans, int my_ans);

int main(int argc, char *argv[])
{
    int ans;
    WINDOW *win;

    /* Initialize curses */
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    //mvprintw(23, 1, "It just a sring");
    refresh();

    /* Load data */
    unsigned char *img = (unsigned char *)calloc(IMG_ROWS * IMG_COLS, sizeof(unsigned char));

    /* Draw img and ans*/
    win = newwin(1 + IMG_ROWS + 1,
                 1 + IMG_COLS + 2 + 2 + 2 + 1,
                 0,
                 0);
    mvprintw(3 + IMG_ROWS, 0, "Now loading...");
    free(img);
    refresh();
    print_img_ans(win, img, 1, 0);

    /* Load data */
    char cwd[100];
    getcwd(cwd, 100);
    string cwd_str(cwd);
    DATASET dataset(cwd_str + "/data/");

    int bingo_cnt = 0;
    int i;
    for (i = 0; i < dataset.test_images.size(); i++)
    {
        img = dataset.test_images[i].data();
        int ans = model_1(img);
        print_img_ans(win, img, dataset.test_labels[i], ans);
        if (dataset.test_labels[i] == ans)
            bingo_cnt++;
    }
    mvprintw(3 + IMG_ROWS, 0, "Total imgs:%d, Currect: %d, Press enter to exit.", dataset.test_labels.size(), bingo_cnt);
    mvprintw(4 + IMG_ROWS, 0, "Key_Left and Key_Right to change img", dataset.test_labels.size(), bingo_cnt);

    /* Wait */
    bool exit = false;
    while (!exit)
    {
        int c = getch();
        switch (c)
        {
        case KEY_LEFT:
            i--;
            if (i < 0)
                i = 0;
            img = dataset.test_images[i].data();
            ans = model_1(img);
            print_img_ans(win, img, dataset.test_labels[i], ans);
            mvprintw(5 + IMG_ROWS, 0, " the img index now:%d", i);
            break;
        case KEY_RIGHT:
            i++;
            if (i >= dataset.test_images.size())
                i = dataset.test_images.size() - 1;
            img = dataset.test_images[i].data();
            ans = model_1(img);
            print_img_ans(win, img, dataset.test_labels[i], ans);
            mvprintw(5 + IMG_ROWS, 0, " the img index now:%d", i);
            break;
        case 10:
            exit = true;
            break;
        }
    }

    /* Free */
    //free(img); if i used calloc
    endwin();

    return 0;
}

/**
 * draw "img = ans"
 */
void print_img_ans(WINDOW *win, const unsigned char *img, int ans, int my_ans)
{
    const unsigned char *p = img;
    int row, col;

    box(win, 0, 0);

    for (row = 0; row < IMG_ROWS; row++)
    {
        wmove(win, row + 1, 1);
        for (col = 0; col < IMG_COLS; col++)
        {
            if (*p == 0)
                waddch(win, ' ');
            else
                waddch(win, '.'); //ACS_CKBOARD);
            p++;
        }
    }

    wmove(win, IMG_ROWS / 2 - 1, 1 + IMG_COLS + 1);
    wprintw(win, " = ");
    waddch(win, '0' + ans);

    wmove(win, IMG_ROWS / 2 + 1, 1 + IMG_COLS + 1);
    wprintw(win, " = ");
    waddch(win, '0' + my_ans);

    wmove(win, IMG_ROWS / 2, 1 + IMG_COLS + 4);
    if (ans != my_ans)
    {
        waddch(win, 'X');
    }
    wrefresh(win);
}
