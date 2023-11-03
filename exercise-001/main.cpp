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

    fmt::print("Value of Variable bss {} adress of variable bss {}\n", foo, fmt::ptr(&foo));
    return 0; /* exit gracefully*/
}
