#include <print>
#include <sstream>

#include "types.hpp"
#include "aoc_helper.cpp"

int main()
{
    auto raw_input{read_file("test.txt")};
    std::println("{}", raw_input);
    // Split input on commas
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
            std::println("{}, {}", ids.first, ids.second);
            data.push_back(ids);
            break;
        }
        pair<string, string> ids = {raw_input.substr(last+1, minus-last-1), raw_input.substr(minus+1, comma-minus-1)};
        std::println("{}, {}", ids.first, ids.second);
        data.push_back(ids);
        last = comma;
    }

    return 0;
}