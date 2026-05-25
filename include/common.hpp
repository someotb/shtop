#pragma once

#include <string>
#include <vector>

struct Process_stats
{
    std::string _name = "";
    int _pid = 0;

    Process_stats() = default;
    ~Process_stats() = default;
};

struct Memory_stats
{
    long long _memtotal = 0;
    long long _memfree = 0;
    long long _memused = 0;

    Memory_stats() = default;
    ~Memory_stats() = default;
};

struct CPU_stats
{
    std::string _name = "";
    long _user = 0;
    long _nice = 0;
    long _system = 0;
    long _idle = 0;
    long _iowait = 0;
    long _irq = 0;
    long _softirq = 0;
    long _steal = 0;
    long _guest = 0;
    long _guest_nice = 0;
    long _total = 0;
    double _usage = 0;

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
