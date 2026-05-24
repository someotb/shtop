#pragma once

#include <string>
#include <vector>

struct Process_stats
{
    std::string _name;
    int _pid;

    Process_stats() = default;
    ~Process_stats() = default;
};

struct Memory_stats
{
    std::string _memtotal;
    std::string _memfree;
    std::string _memused;

    Memory_stats() = default;
    ~Memory_stats() = default;
};

struct CPU_stats
{
    std::string _name;
    long _user;
    long _nice;
    long _system;
    long _idle;
    long _iowait;
    long _irq;
    long _softirq;
    long _steal;
    long _guest;
    long _guest_nice;
    long _total;
    double _usage;

    CPU_stats() = default;
    ~CPU_stats() = default;
};

struct Common
{
    std::vector<Process_stats> p;
    std::vector<Memory_stats> m;
    std::vector<CPU_stats> c;

    Common() = default;
    ~Common() = default;
};
