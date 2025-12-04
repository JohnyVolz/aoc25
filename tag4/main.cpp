#include <print>
#include <sstream>
#include <filesystem>
#include <string>
#include <cmath>

#include "types.hpp"
#include "aoc_helper.cpp"

int main()
{
    std::filesystem::path p{"test.txt"};
    auto raw_input{read_file_to_grid(p)};

    // for (auto line : raw_input)
    // {
    //     for (auto entry : line)
    //     {
    //         std::print("{}", entry);
    //     }
    //     std::println("");
    // }

    vector<pair<int32, int32>> dirs{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    int32 movable{0};
    for (auto row{0}; row < raw_input.size(); ++row)
    {
        for (auto col{0}; col < raw_input.at(row).size(); ++col)
        {
            if (raw_input.at(row).at(col) != "@")
            {
                continue;
            }
            int32 count{0};
            for (auto dir : dirs)
            {
                if (row + dir.first >= 0 && row + dir.first < raw_input.size() && col + dir.second >= 0 && col + dir.second < raw_input.at(row).size() && raw_input.at(row + dir.first).at(col + dir.second) == "@")
                {
                    count += 1;
                }
            }
            if (count < 4)
            {
                movable += 1;
            }
        }
    }
    std::println("Part 1: {}", movable);

    movable = 0;
    auto new_grid{raw_input};
    bool removed{true};
    while (removed)
    {
        removed = false;
        for (auto row{0}; row < raw_input.size(); ++row)
        {
            for (auto col{0}; col < raw_input.at(row).size(); ++col)
            {
                if (raw_input.at(row).at(col) != "@")
                {
                    continue;
                }
                int32 count{0};
                for (auto dir : dirs)
                {
                    if (row + dir.first >= 0 && row + dir.first < raw_input.size() && col + dir.second >= 0 && col + dir.second < raw_input.at(row).size() && raw_input.at(row + dir.first).at(col + dir.second) == "@")
                    {
                        count += 1;
                    }
                }
                if (count < 4)
                {
                    movable += 1;
                    new_grid.at(row).at(col) = "x";
                    removed = true;
                }
            }
        }
        raw_input = new_grid;
    }

    std::println("Part 2: {}", movable);

    return 0;
}

// cd ../build && cmake --build . && cp tag4.out ../tag4/tag4.out && cd ../tag4 && ./tag4.out