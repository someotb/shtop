#pragma once

#include <string>

struct Process
{
    std::string _name;
    int _pid;

    Process() = default;
    ~Process() = default;
};
