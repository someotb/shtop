#pragma once

#include "common.hpp"
#include <ncurses.h>

void centered_label(WINDOW &win, const std::string &label);
void run_app(Common &common);
