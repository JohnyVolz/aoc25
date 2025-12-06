#include <print>
#include <sstream>
#include <filesystem>
#include <cmath>

#include "../auxilary/types.hpp"
#include "../auxilary/aoc_helper.cpp"

namespace fs = std::filesystem;

int main()
{
    fs::path parent_path{fs::current_path().parent_path()};
    fs::path test_file_path{parent_path / "tag5" / "test.txt"};
    fs::path input_file_path{parent_path / "tag5" / "input.txt"};
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


    // auto data = test_data;
    auto data = input_data;
    size_t separator{data.find("\n\n")};
    std::stringstream s_ranges{data.substr(0,separator)};
    string range{};

    vector<pair<int64, int64>> ranges{};
    while (std::getline(s_ranges,range))
    {
        size_t minus {range.find("-")};
        ranges.push_back({std::stoll(range.substr(0,minus)), std::stoll(range.substr(minus+1))});
    }

    // std::stringstream food{data.substr(separator+2)};
    // string id{};
    // int64 sum{0};
    // while (std::getline(food, id))
    // {   
    //     int64 i_id{std::stoll(id)};
    //     for (auto r: ranges)
    //     {
    //         if (i_id >= r.first && i_id <= r.second)
    //         {
    //             sum += 1;
    //             // std::println("{}", i_id);
    //             break;
    //         }
    //     }
    // }
    // std::println("{}", sum);
    std::println("Start");
    vector<pair<int64, int64>> prev_ranges{};
    int64 fresh{0};
    for (auto r: ranges)
    {   
        int64 start{r.first};
        int64 end{r.second};
        for (auto pr: prev_ranges)
        {
            if (r == pr)
            {
                std::println("Pairing: {},{}", pr.first, pr.second);
                start = 1;
                end = 0;
                break;
            }
            if (start >= pr.first && start <= pr.second)
            {
                if (end > pr.second)
                {
                    start = pr.second+1;
                }
                else
                {
                    std::println("Nothing left");
                    start = end + 1;
                    break;
                }
            }
            if (end >= pr.first && end <= pr.second)
            {
                if (start < pr.first)
                {
                    end = pr.first-1;
                }
                else
                {
                    std::println("Empty");
                    end = start - 1;
                }
            }

        }
        prev_ranges.push_back(r);
        std::println("{}, {}, {}", start, end, end-start+1);
        if (start <= end)
        {
            fresh += end-start+1;
        }
    }
    std::println("{}", fresh);
    return 0;
}

// cmake --build . && ./tag5.out

// 349857423070633
