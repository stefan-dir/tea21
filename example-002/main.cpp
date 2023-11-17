#include <fmt/format.h>
#include <vector>

auto main(int argc, char** argv) -> int
{
    struct Test
    {
        char data[9];
        // Padding Bytes
        int foo;
        void print () {
            fmt::println("Value of foo");
        }
    };
    Test tt;
    tt.print();
    char data[] = "None terminated string!!";
    Test testers[10];
    std::vector<int> vec(100);
    std::vector<Test> vec_tester(42);
    int* pInt;
    fmt::println("The size of data[] {}",sizeof(data));
    fmt::println("The size of argv[0] {}",sizeof(argv[0]));
    fmt::println("The strlen of argv[0] {}",strlen(argv[0]));
    fmt::println("The sizeof(vec): {}",sizeof(vec));
    fmt::println("The vec.size(): {}",vec.size());
    fmt::println("The sizeof(pInt): {}",sizeof(pInt));
    fmt::println("The sizeof(Test): {}",sizeof(Test));
    fmt::println("The sizeof(int): {}",sizeof(int));
    fmt::println("The sizeof(testers): {}",sizeof(testers));
    fmt::println("The number of elements in testers: {}",sizeof(testers)/sizeof(Test));
    fmt::println("The vec_tester.size(): {}",vec_tester.size());
    return 0;
}
