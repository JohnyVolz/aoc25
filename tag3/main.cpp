#include <print>
#include <sstream>
#include <filesystem>
#include <string>
#include <cmath>

#include "types.hpp"
#include "aoc_helper.cpp"


int64 find_number (vector<int64> numbers, int32 places){
    int64 res {0};
    int32 start {0};
    for (auto p {0}; p < places; ++p){
        int64 num {-1};
        int32 pos {-1};
        for (auto i{start}; i < numbers.size() - (places-p-1); ++i)
        {
            if (numbers.at(i) > num){
                num = numbers.at(i);
                pos = i;
            }
        }
        if (num == -1 || pos == -1){
            throw;
        }
        start = pos+1;
        res += num * int64(std::pow(10, places-p-1));
    }
    return res;
}

int main()
{
    std::filesystem::path p{"input.txt"};
    auto raw_input{read_file(p)};

    // std::println("{}", raw_input);

    int64 result_1 {0};
    int64 result_2 {0};

    vector<int64> current_line;

    for (auto c : raw_input)
    {
        if (c == '\n')
        {   
            result_1 += find_number(current_line, 2);
            result_2 += find_number(current_line, 12);
            current_line.clear();
            continue;
        }
        int64 s{c - '0'};
        current_line.push_back(s);
    }

    std::println("Part 1: {}", result_1);
    std::println("Part 2: {}", result_2);
    return 0;
}

// cd ../build && cmake --build . && cp tag2.out ../tag2/tag2.out && cd ../tag2 && ./tag2.out