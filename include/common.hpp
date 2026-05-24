#pragma once

#include <string>
#include <vector>

struct Process
{
    std::string _name;
    int _pid;

    Process() = default;
    ~Process() = default;
};

struct Memory
{
    std::string _memtotal;
    std::string _memfree;
    std::string _memused;

    Memory() = default;
    ~Memory() = default;
};

struct Common
{
    std::vector<Process> p;
    std::vector<Memory> m;

    Common() = default;
    ~Common() = default;
};
