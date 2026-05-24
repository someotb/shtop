#pragma once

#include "common.hpp"

#include <string>
#include <filesystem>

std::string get_pid_name(const int pid, const std::filesystem::path &p);
void mem_info(Common &common);
void pid_info(Common &common);
void cpu_info(Common &common);
