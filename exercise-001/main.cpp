#include <fmt/chrono.h>
#include <fmt/format.h>

#include <iostream>
#include <random>

#include "CLI/CLI.hpp"
#include "config.h"

// .bss segment;
int foo;

// .data segment
int data = 4711;

// .rodata segment
const int rodata = 42;


auto main(int argc, char **argv) -> int
{
    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", "hah");
    
    // .stack segment
    
    int stack2;
    int stack = 5;
    

    fmt::print("Value of Variable bss {} address of variable bss {}\n", foo, fmt::ptr(&foo));
    fmt::print("Value of Variable data {} address of variable bss {}\n", data, fmt::ptr(&data));
    fmt::print("Value of Variable rodata {} address of variable rodata {}\n", rodata, fmt::ptr(&rodata));
    fmt::print("Value of Variable stack {} address of variable stack {}\n", stack, fmt::ptr(&stack));
    fmt::print("Value of Variable stack2 {} address of variable stack2 {}\n", stack2, fmt::ptr(&stack2));


    return 0; /* exit gracefully*/
}
