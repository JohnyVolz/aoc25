#include <print>
#include <sstream>
#include <filesystem>
#include <cmath>

#include "../auxilary/types.hpp"
#include "../auxilary/errors.hpp"
#include "../auxilary/aoc_helper.cpp"

namespace fs = std::filesystem;

int main()
{
    fs::path parent_path{fs::current_path().parent_path()};
    fs::path test_file_path{parent_path / "TAG" / "test.txt"};
    fs::path input_file_path{parent_path / "TAG" / "input.txt"};
    fs::directory_entry test_file{test_file_path};
    fs::directory_entry input_file{input_file_path};
    if (!test_file.exists() || !test_file.is_regular_file())
    {
        throw std::runtime_error("file does not exist: " + test_file_path.string());
    }
    if (!input_file.exists() || !input_file.is_regular_file())
    {
        throw std::runtime_error("file does not exist: " + input_file_path.string());
    }

    auto test_data{read_file(test_file.path().string())};
    auto input_data{read_file(input_file.path().string())};

    return 0;
}
