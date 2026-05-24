#include "proc_parse.hpp"
#include "common.hpp"

#include <cctype>
#include <chrono>
#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <thread>
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

void mem_info(Common &common)
{
    std::ifstream mem("/proc/meminfo");

    if (!mem.is_open())
        throw std::runtime_error("/proc/meminfo unavailable");

    std::string line;
    long int memtotal = 0;
    long int memfree = 0;
    Memory_stats memory;

    while (std::getline(mem, line))
    {
        std::string name;
        long int val;
        std::istringstream stream(line);
        stream >> name >> val;
        if (name == "MemTotal:")
            memory._memtotal = val;
        if (name == "MemFree:")
            memory._memfree = val;
        if (memtotal && memfree)
            break;
    }

    memory._memused =  memtotal - memfree;
}

void pid_info(Common &common)
{
    std::filesystem::path proc("/proc");
    if (!std::filesystem::exists(proc) || !std::filesystem::is_directory(proc))
        throw std::runtime_error("func(pid_info) /proc unavailable");

    for (const auto &e : std::filesystem::directory_iterator(proc))
    {
        std::string name = e.path().filename();
        if (std::all_of(name.begin(), name.end(), ::isdigit))
        {
            Process_stats p;
            p._pid = std::stoi(name);
            p._name = get_pid_name(p._pid, proc);
            if (p._name.empty()) continue;
            common.p.push_back(p);
        }
    }
}

CPU_stats get_cpu_stats()
{
    std::ifstream cpu_stat("/proc/stat");
    if (!cpu_stat.is_open())
        throw std::runtime_error("func(cpu_info): Failed to open /proc/stat");

    std::string cpu_usage;
    CPU_stats c;
    std::getline(cpu_stat, cpu_usage);
    std::istringstream stream(cpu_usage);
    stream >> c._name >> c._user >> c._nice >> c._system >> c._idle >> c._iowait >> c._irq >> c._softirq >> c._steal >> c._guest >> c._guest_nice;
    c._total = c._user + c._nice + c._system + c._idle + c._iowait + c._irq + c._softirq + c._steal + c._guest + c._guest_nice;
    return c;
}

void cpu_info(Common &common)
{
    std::chrono::milliseconds delta = std::chrono::milliseconds(0);
    auto start = std::chrono::steady_clock::now();
    CPU_stats cpu1 = get_cpu_stats();
    long cpu_total1 = cpu1._total;
    long cpu_idle1 = cpu1._idle;

    while (delta.count() < 1000)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        auto end = std::chrono::steady_clock::now();
        delta = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }

    CPU_stats cpu2 = get_cpu_stats();
    long cpu_total2 = cpu2._total;
    long cpu_idle2 = cpu2._idle;

    long delta_total = cpu_total2 - cpu_total1;
    long delta_idle = cpu_idle2 - cpu_idle1;

    double cpu_usage = (1 - static_cast<double>(delta_idle) / static_cast<double>(delta_total)) * 100;
    cpu2._usage = cpu_usage;
    common.c.push_back(cpu2);
}
