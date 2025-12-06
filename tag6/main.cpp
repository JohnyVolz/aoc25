#include <print>
#include <sstream>
#include <filesystem>
#include <cmath>

#include "../auxilary/types.hpp"
#include "../auxilary/errors.hpp"
#include "../auxilary/aoc_helper.cpp"

namespace fs = std::filesystem;

int64 part_1(const string& data)
{
    int64 result{0};
    stringstream data_stream{data};
    string line{};
    vector<vector<int64>> numbers{};
    vector<string> operation{};
    while (std::getline(data_stream, line))
    {
        stringstream line_stream{line};
        if (line.find("+") == string::npos || line.find("*") == string::npos)
        {
            int64 num{};
            vector<int64> row{};
            while (line_stream >> num)
            {
                row.push_back(num);
            }
            numbers.push_back(row);
        }
        else
        {
            string op{};
            while (line_stream >> op)
            {
                operation.push_back(op);
            }
        }
    }

    for (auto i{0}; i < operation.size(); ++i)
    {   
        int32 temp{operation.at(i) == "*" ? 1 : 0};
        for (auto j{0}; j < numbers.size(); ++j)
        {
            if (operation.at(i) == "*")
            {
                temp *= numbers.at(j).at(i);
            }
            else
            {
                temp += numbers.at(j).at(i);
            }
        }
        result += temp;
    }


    return result;
}

int64 part_2(const string& data)
{
    int64 result{0};
    stringstream data_stream{data};
    string line{};
    vector<string> transposed{};
    vector<string> operation{};
    while (std::getline(data_stream, line))
    {
        if (transposed.size() == 0)
        {   
            for (auto i{0}; i < line.size(); ++i)
            {
                transposed.push_back(line.substr(i,1));
            }
        }
        else if (line.find("+") == string::npos || line.find("*") == string::npos)
        {
            for (auto i{0}; i < line.size(); ++i)
            {
                transposed.at(i).append(line.substr(i,1));
            }
        }
        else
        {
            string op{};
            stringstream line_stream{line};
            while (line_stream >> op)
            {
                operation.push_back(op);
            }
            std::print("");
        }
    }
    int32 i{0};
    int64 temp{operation.at(i) == "*" ? 1 : 0};
    for (auto l: transposed)
    {   
        try
        {
            if (operation.at(i) == "*")
            {
                temp *= std::stoll(l);
            }
            else
            {
                temp += std::stoll(l);
            }
        }
        catch (...)
        {
            ++i;
            result += temp;
            temp = operation.at(i) == "*" ? 1 : 0;
        }

    }
    result += temp;
    return result;
}

int main()
{
    fs::path parent_path{fs::current_path().parent_path()};
    fs::path test_file_path{parent_path / "tag6" / "test.txt"};
    fs::path input_file_path{parent_path / "tag6" / "input.txt"};
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

    auto test_result_part_1{part_1(test_data)};
    std::println("Test Part 1: {}, should be 4277556", test_result_part_1);
    auto result_part_1{part_1(input_data)};
    std::println("Result Part 1: {}", result_part_1);

    auto test_result_part_2{part_2(test_data)};
    std::println("Test Part 2: {}, should be 3263827", test_result_part_2);
    auto result_part_2{part_2(input_data)};
    std::println("Result Part 2: {}", result_part_2);


    

    return 0;
}

// cmake --build . && ./tag6.out
