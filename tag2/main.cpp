#include <print>
#include <sstream>
#include <filesystem>
#include <cmath>

#include "../auxilary/types.hpp"
#include "../auxilary/aoc_helper.cpp"

namespace fs = std::filesystem;

void part1(vector<pair<string, string>> data)
{
    int64 result{0};
    for (const auto &[id1, id2] : data)
    {
        if (id1.size() % 2 && id2.size() % 2)
        {
            continue;
        }
        size_t half1{id1.size() / 2};
        size_t half2{id2.size() / 2 + id2.size() % 2};
        int64 start{std::stoll(id1)};
        int64 end{std::stoll(id2)};
        if (half1 == 0 && half2 == 0)
        {
            continue;
        }
        int64 start_half{};
        int64 end_half{};
        if (half1 == 0 && half2 > 0)
        {
            start_half = std::stoi("1");
            end_half = std::stoi(id2.substr(0, half2));
        }
        else
        {
            start_half = std::stoi(id1.substr(0, half1));
            end_half = std::stoi(id2.substr(0, half2));
        }
        for (auto i{start_half}; i <= end_half; ++i)
        {
            string num{std::to_string(i)};
            uint64 length{num.size()};
            int64 test{i * static_cast<int64>(std::pow(10, length)) + i};
            if (test >= start && test <= end)
            {
                // std::println("{}", test);
                result += test;
            }
            // for (auto j{1}; j < length; ++j)
            // {
            //     int64 test2{0};
            //     int64 seq{std::stoll(num.substr(0, j))};
            //     for (auto x{j}; x < length; x + j)
            //     {
            //         test2 = test2 * std::pow(10, j) + seq;
            //     }
            //     if (test2 >= start && test2 <= end)
            //     {
            //         std::println("{}", test2);
            //         result2 += test2;
            //     }
            // }
        }

        // std::println("{}, {}", half1, half2);
    }
    std::println("Part 1: {}", result);
}

int main()
{   
    fs::path parent_path{fs::current_path().parent_path()};
    fs::path file_path{parent_path / "tag2" / "input.txt"};
    fs::directory_entry dirEntry{file_path};
    if (!dirEntry.exists() || !dirEntry.is_regular_file())
    {
        throw std::runtime_error("file does not exist: " + file_path.string());
    }

    auto raw_input{read_file(dirEntry.path().string())};

    // Split input into pairs
    vector<pair<string, string>> data{};
    int32 last{0};
    while (true)
    {
        size_t minus{raw_input.find("-", last)};
        size_t comma{raw_input.find(",", last + 1)};

        if (minus == string::npos)
        {
            break;
        }
        if (comma == string::npos)
        {
            pair<string, string> ids = {raw_input.substr(last + 1, minus - last - 1), raw_input.substr(minus + 1)};
            data.push_back(ids);
            break;
        }
        pair<string, string> ids = {raw_input.substr(last + 1, minus - last - 1), raw_input.substr(minus + 1, comma - minus - 1)};
        data.push_back(ids);
        last = comma;
    }

    // // Print pairs
    // for (const auto& [id1, id2] : data)
    // {
    //     std::println("{}, {}", id1, id2);
    // }

    part1(data);

    return 0;
}

// cd ../build && cmake --build . && cp tag2.out ../tag2/tag2.out && cd ../tag2 && ./tag2.out