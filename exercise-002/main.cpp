#include <stdlib.h>
#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

auto main(int argc, char **argv) -> int
{   
    auto counter = 20;
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.add_option("-c,--count", counter, fmt::format("counter with default value: {}", counter));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    std::vector<int> data(counter);
    fmt::print("counter param: {}\n", counter);
    fmt::print("created a vector with size of counter: {}\n", data.size());


    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", app.get_name());

    /* INSERT YOUR CODE HERE */
    for (auto& i : data){
        i = std::rand() % 101;
    }
    fmt::print("Content of data: [{}]",fmt::join(data,", "));

    return 0; /* exit gracefully*/
}
