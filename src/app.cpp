#include "app.hpp"
#include "proc_parse.hpp"

#include <ncurses.h>

void centered_label(WINDOW *win, const std::string &label)
{
    int width = getmaxx(win);
    mvwhline(win, 0, 1, ACS_HLINE, width - 2);
    mvwprintw(win, 0, (width - label.size()) / 2, "%s", label.c_str());
}

void run_app(Common &common)
{
    initscr();
    timeout(0);
    noecho();
    curs_set(0);

    WINDOW *cpu_win = newwin(5, 20, 0, 0);
    WINDOW *mem_win = newwin(5, 20, 0, 20);
    WINDOW *pid_win = newwin(100, 200, 5, 0);

    while (true)
    {
        update_stats(common);

        // CPU окно
        werase(cpu_win);
        box(cpu_win, 0, 0);
        centered_label(cpu_win, "CPU INFO");
        if (!common.c.empty())
        {
            mvwprintw(cpu_win, 1, 1, "Name: %s", common.c.back()._name.c_str());
            mvwprintw(cpu_win, 2, 1, "Usage: %.2f%%", common.c.back()._usage);
        }

        // MEM окно
        werase(mem_win);
        box(mem_win, 0, 0);
        centered_label(mem_win, "MEM INFO");
        if (!common.m.empty())
        {
            mvwprintw(mem_win, 1, 1, "Total: %.2f GB", common.m.back()._memtotal / 1024.0 / 1024.0);
            mvwprintw(mem_win, 2, 1, "Free:  %.2f GB", common.m.back()._memfree  / 1024.0 / 1024.0);
            mvwprintw(mem_win, 3, 1, "Used:  %.2f GB", common.m.back()._memused  / 1024.0 / 1024.0);
        }

        // PID окно
        werase(pid_win);
        box(pid_win, 0, 0);
        centered_label(pid_win, "PID INFO");
        if (!common.p.empty())
        {
            mvwprintw(pid_win, 1, 1, "PID count: %ld", common.p.size());
            int x = 2;
            for (const auto &p : common.p)
            {
                int y = 1;
                mvwprintw(pid_win, x, y, "PID: %d | Name: %s", p._pid, p._name.c_str());
                x += 1;
            }
        }

        wrefresh(cpu_win);
        wrefresh(mem_win);
        wrefresh(pid_win);

        int ch = getch();
        flushinp();
        if (ch == 'q') break;
    }

    delwin(cpu_win);
    delwin(mem_win);
    delwin(pid_win);
    endwin();
}
