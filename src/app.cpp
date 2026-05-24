#include "app.hpp"
#include "proc_parse.hpp"

#include <ncurses.h>

void run_app(Common &common)
{
    initscr();
    timeout(0);
    while (true)
    {
        update_stats(common);
        clear();
        mvprintw(0, 0, "CPU INFO");
        mvprintw(1, 0, "CPU name: %s", common.c.back()._name.c_str());
        mvprintw(2, 0, "CPU usage: %.2f", common.c.back()._usage);
        refresh();
        int ch = getch();
        flushinp();
        if (ch == 'q') break;
    }
    endwin();
}
