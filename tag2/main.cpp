#include <print>
#include <sstream>
#include <filesystem>

#include "types.hpp"
#include "aoc_helper.cpp"

int main()
{
    std::filesystem::path p{"test.txt"};
    auto raw_input{read_file(p)};

    // Split input into pairs
    vector<pair<string, string>> data{};
    size_t last{0};
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

    // Print pairs
    for (const auto& [id1, id2] : data)
    {
        std::println("{}, {}", id1, id2);
    }


    for (const auto& [id1, id2] : data)
    {
        if (id1.size()%2 && id2.size()%2)
        {
            continue;
        }
        size_t half1 {id1.size()/2};
        size_t half2 {id2.size()/2};
        std::println("{}, {}", half1, half2);
    }

    return 0;
}

// cd ../build && cmake --build . && cp tag2.out ../tag2/tag2.out && cd ../tag2 && ./tag2.out