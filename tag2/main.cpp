#include <print>
#include <sstream>
#include <filesystem>
#include <cmath>

#include "types.hpp"
#include "aoc_helper.cpp"

int main()
{
    std::filesystem::path p{"input.txt"};
    auto raw_input{read_file(p)};

    // Split input into pairs
    vector<pair<string, string>> data{};
    int32 last{0};
    while (true)
    {
        size_t minus {raw_input.find("-", last)};
        size_t comma {raw_input.find(",", last+1)};

        if (minus == string::npos)
        {
            break;
        }
        if (comma == string::npos)
        {   
            pair<string, string> ids = {raw_input.substr(last+1, minus-last-1), raw_input.substr(minus+1)};
            data.push_back(ids);
            break;
        }
        pair<string, string> ids = {raw_input.substr(last+1, minus-last-1), raw_input.substr(minus+1, comma-minus-1)};
        data.push_back(ids);
        last = comma;
    }

    // // Print pairs
    // for (const auto& [id1, id2] : data)
    // {
    //     std::println("{}, {}", id1, id2);
    // }

    int64 result {0};
    for (const auto& [id1, id2] : data)
    {
        if (id1.size()%2 && id2.size()%2)
        {
            continue;
        }
        size_t half1 {id1.size()/2};
        size_t half2 {id2.size()/2 + id2.size()%2};
        int64 start {std::stoi(id1)};
        int64 end {std::stoi(id2)};
        if (half1 == 0 && half2 == 0)
        {
            continue;
        }
        int64 start_half {};
        int64 end_half {};
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
        for (auto i {start_half}; i <= end_half; ++i)
            {
                uint64 length {std::to_string(i).size()};
                int64 test {i * static_cast<int64>(std::pow(10, length)) + i};
                if (test >= start && test <= end){
                    // std::println("{}", test);
                    result += test;
                }

            }

        // std::println("{}, {}", half1, half2);
    }
    std::println("{}", result);

    return 0;
}

// cd ../build && cmake --build . && cp tag2.out ../tag2/tag2.out && cd ../tag2 && ./tag2.out