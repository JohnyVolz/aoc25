#include <print>
#include <sstream>


#include "types.hpp"
#include "aoc_helper.cpp"



int main()
{
    auto raw_input = read_file_to_vector("input.txt");

    /// Part 1
    int32 x = 50;
    int32 zeros = 0;
    for (const auto& line : raw_input)
    {
        string dir = line.substr(0, 1);
        int32 val = std::stoi(line.substr(1));
        if (dir == "R"){
            x += val;
        } else {
            x -= val;
        }
        x %= 100;
        if (x < 0)
            x += 100;
        if (x == 0)
            zeros += 1;
    }
    std::println("Zeros: {}", zeros);

    /// Part 2
    x = 50;
    zeros = 0;
    for (const auto& line : raw_input)
    {
        string dir = line.substr(0, 1);
        int32 val = std::stoi(line.substr(1));
        for (auto i = 0; i < val; ++i){
            if (dir == "R"){
                x += 1;
            } else {
                x += 99;
            }
            x %= 100;
            if (x == 0)
                zeros += 1;
        }
        
    }
    std::println("Zeros + crossings: {}", zeros);

    /// Part 2 - fehlerhaft
    x = 50;
    zeros = 0;
    for (const auto& line : raw_input)
    {
        string dir = line.substr(0, 1);
        int32 val = std::stoi(line.substr(1));
        int32 quotient = val / 100;
        int32 reminder = val % 100;
        zeros += quotient;
        if (dir == "R"){
            x += reminder;
            if (x >= 100){
                zeros += 1;
                x -= 100;   
            }
        } else {
            x -= reminder;
            if (x < 0){
                zeros += 1;
                x += 100;   
            }
        }
        
        
    }
    std::println("Zeros + crossings: {}", zeros);

    return 0;
}