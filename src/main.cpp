#include "proc_parse.hpp"

#include <iostream>

int main()
{
    Common comon;

    mem_info(comon);
    pid_info(comon);
    cpu_info(comon);

    std::cout << comon.c.back()._usage << "\n";

    return 0;
}
