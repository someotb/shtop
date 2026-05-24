#pragma once

#include <string>
#include <filesystem>

std::string get_pid_name(const int pid, const std::filesystem::path &p);
void mem_info();
void pid_info();
