#include "app.hpp"
#include "proc_parse.hpp"

#include <ncurses.h>
#include <thread>
#include <chrono>

void run_app(Common &common)
{
    initscr();
    timeout(0);
    while (true)
    {
        update_stats(common);
        mvprintw(0, 0, "CPU INFO");
        mvprintw(1, 0, "CPU name: %s", common.c.back()._name.c_str());
        mvprintw(2, 0, "CPU usage: %.1f", common.c.back()._usage);
        refresh();
        getch();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    endwin();
}
