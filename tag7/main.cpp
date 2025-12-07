#include <print>
#include <sstream>
#include <filesystem>
#include <cmath>

#include "../auxilary/types.hpp"
#include "../auxilary/errors.hpp"
#include "../auxilary/aoc_helper.cpp"

namespace fs = std::filesystem;

int64 part_1(string& data)
{
    int64 result{0};
    stringstream data_stream{data};
    string line{};
    vector<int32> lasers;
    while (std::getline(data_stream, line))
    {
        size_t s_pos{line.find("S")};
        if (s_pos != string::npos)
        {
            lasers.push_back(s_pos);
        }
        if (line.find("^") == string::npos) 
        {
            continue;
        }

        size_t pos_spliter{line.find("^", 0)};
        while(pos_spliter != string::npos)
        {
            auto laser{std::find(lasers.begin(), lasers.end(), pos_spliter)};
            if (laser != lasers.end())
            {
                lasers.erase(laser);
                result += 1;
                auto laser_left{std::find(lasers.begin(), lasers.end(), pos_spliter-1)};
                if (laser_left == lasers.end())
                {
                    lasers.push_back(pos_spliter-1);
                }
                auto laser_right{std::find(lasers.begin(), lasers.end(), pos_spliter+1)};
                if (laser_right == lasers.end())
                {
                    lasers.push_back(pos_spliter+1);
                }
            }
            pos_spliter = line.find("^",pos_spliter+1);
        }

    }

    return result;
}

int64 part_2(string& data)
{
    int64 result{0};
    stringstream data_stream{data};
    string line{};
    map<size_t, int64> paths{};
    while (std::getline(data_stream, line))
    {   
        size_t s_pos{line.find("S")};
        if (s_pos != string::npos)
        {
            paths.insert({s_pos, 1});
            continue;
        }
        if (line.find("^") == string::npos) 
        {
            continue;
        }
        
        map<size_t, int64> new_paths{};
        size_t pos_spliter{line.find("^", 0)};
        while(pos_spliter != string::npos)
        {
            if (paths.contains(pos_spliter))
            {
                if (new_paths.contains(pos_spliter-1))
                {
                    new_paths.at(pos_spliter-1) += paths.at(pos_spliter);
                }
                else
                {
                    new_paths.insert({pos_spliter-1, paths.at(pos_spliter)});
                }

                if (new_paths.contains(pos_spliter+1))
                {
                    new_paths.at(pos_spliter+1) += paths.at(pos_spliter);
                }
                else
                {
                    new_paths.insert({pos_spliter+1, paths.at(pos_spliter)});
                }
                paths.erase(pos_spliter);
            }        
            pos_spliter = line.find("^",pos_spliter+1);
        }
        for (auto p: paths)
        {   
            if (new_paths.contains(p.first))
                {
                    new_paths.at(p.first) += p.second;
                }
                else
                {
                    new_paths.insert(p);
                }
        }
        paths = new_paths;
    }
    for (auto p: paths)
    {
        result += p.second;
    }
    
    return result;
}

int main()
{
    fs::path parent_path{fs::current_path().parent_path()};
    fs::path test_file_path{parent_path / "tag7" / "test.txt"};
    fs::path input_file_path{parent_path / "tag7" / "input.txt"};
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

    // auto test_result_part_1{part_1(test_data)};
    // auto result_part_1{part_1(input_data)};
    // std::println("Part 1:");
    // std::println("Test {}, correct is 21", test_result_part_1);
    // std::println("Result: {}", result_part_1);
    // std::println("");

    auto test_result_part_2{part_2(test_data)};
    auto result_part_2{part_2(input_data)};
    std::println("Part 2:");
    std::println("Test {}, correct is 40", test_result_part_2);
    std::println("Result: {}", result_part_2);
    std::println("");


    return 0;
}

// cmake --build . && ./tag7.out
