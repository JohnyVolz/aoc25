#include <print>
#include <sstream>
#include <filesystem>
#include <cmath>

#include "../auxilary/types.hpp"
#include "../auxilary/errors.hpp"
#include "../auxilary/aoc_helper.cpp"

namespace fs = std::filesystem;

int64 part_1(string &data)
{
    int64 result{0};

    return result;
}

int64 part_2(string &data)
{
    int64 result{0};

    return result;
}

int main()
{
    fs::path parent_path{fs::current_path().parent_path()};
    fs::path test_file_path{parent_path / "TAG" / "test.txt"};
    fs::path input_file_path{parent_path / "TAG" / "input.txt"};
    
    auto test_data{read_file(test_file_path)};
    auto input_data{read_file(input_file_path)};

    auto test_result_part_1{part_1(test_data)};
    std::println("Part 1:");
    std::println("Test {}, correct is ...", test_result_part_1);
    auto result_part_1{part_1(input_data)};
    std::println("Result: {}", result_part_1);

    auto test_result_part_2{part_2(test_data)};
    std::println("Part 2:");
    std::println("Test {}, correct is ...", test_result_part_2);
    auto result_part_2{part_2(input_data)};
    std::println("Result: {}", result_part_2);

    return 0;
}
