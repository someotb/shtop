#include "proc_parse.hpp"
#include "common.hpp"

#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <algorithm>
#include <vector>

std::string get_pid_name(const int pid, const std::filesystem::path &p)
{
    std::filesystem::path pid_name = p / std::to_string(pid) / "status";
    std::ifstream name = pid_name;

    if (!name.is_open())
        return "";

    std::string line;
    std::string field_name;
    std::string field_real_name;
    std::getline(name, line);
    std::istringstream stream(line);
    stream >> field_name >> field_real_name;
    return field_real_name;
}

void mem_info()
{
    std::ifstream mem("/proc/meminfo");

    if (!mem.is_open())
        throw std::runtime_error("/proc/meminfo unavailable");

    std::string line;
    long int memtotal = 0;
    long int memfree = 0;

    while (std::getline(mem, line))
    {
        std::string name;
        long int val;
        std::istringstream stream(line);
        stream >> name >> val;
        if (name == "MemTotal:")
        {
            std::cout << name << val << std::endl;
            memtotal = val;
        }
        if (name == "MemFree:")
        {
            std::cout << name << val << std::endl;
            memfree = val;
        }

        if (memtotal && memfree)
            break;
    }

    std::cout << "MemUsed:" << memtotal - memfree << std::endl;
}

void pid_info()
{
    std::vector<Process> processes;
    std::filesystem::path proc("/proc");
    if (!std::filesystem::exists(proc) || !std::filesystem::is_directory(proc))
        throw std::runtime_error("func(pid_info) /proc unavailable");

    for (const auto &e : std::filesystem::directory_iterator(proc))
    {
        std::string name = e.path().filename();
        if (std::all_of(name.begin(), name.end(), ::isdigit))
        {
            Process p;
            p._pid = std::stoi(name);
            p._name = get_pid_name(p._pid, proc);
            if (p._name.empty()) continue;
            processes.push_back(p);
        }
    }

    for (const auto &p : processes)
        std::cout << "PID: " << p._pid << " | NAME: " << p._name << "\n";
}
