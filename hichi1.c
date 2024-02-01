#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int main(){
    initscr();

    printw("Hello World!");

    refresh();

    int c = getch();

    printw("%d", c);

    getch();

    endwin();

    return 0;    
}