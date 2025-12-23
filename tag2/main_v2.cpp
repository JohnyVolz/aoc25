#include <print>
#include <sstream>
#include <filesystem>
#include <cmath>

#include "../auxilary/types.hpp"
#include "../auxilary/errors.hpp"
#include "../auxilary/aoc_helper.cpp"

namespace fs = std::filesystem;

int64 part_1(string& raw_input)
{
    // Split input into pairs
    vector<pair<string, string>> ranges{};
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
            ranges.push_back(ids);
            break;
        }
        pair<string, string> ids = {raw_input.substr(last + 1, minus - last - 1), raw_input.substr(minus + 1, comma - minus - 1)};
        ranges.push_back(ids);
        last = comma;
    }

    int64 result{0};
    for (const auto &[id1, id2] : ranges)
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
                result += test;
            }
        }

    }
    
    return result;
}

int64 part_2(string& raw_input)
{
    // Split input into pairs
    vector<pair<string, string>> ranges{};
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
            ranges.push_back(ids);
            break;
        }
        pair<string, string> ids = {raw_input.substr(last + 1, minus - last - 1), raw_input.substr(minus + 1, comma - minus - 1)};
        ranges.push_back(ids);
        last = comma;
    }
    int64 result{0};
    set<int64> invalid_ids{};
    for (const auto &[id1, id2] : ranges)
    {
        size_t len_half1{id1.size() / 2};
        size_t len_half2{id2.size() / 2 + id2.size() % 2};
        int64 start{std::stoll(id1)};
        int64 end{std::stoll(id2)};
        if (len_half1 == 0 && len_half2 == 0)
        {
            continue;
        }
        int64 start_half{};
        int64 end_half{};
        if (len_half1 == 0 && len_half2 > 0)
        {
            start_half = std::stoll("1");
            end_half = std::stoll(id2.substr(0, len_half2));
        }
        else
        {
            start_half = std::stoll(id1.substr(0, len_half1));
            end_half = std::stoll(id2.substr(0, len_half2));
        }
        for (auto i{start_half}; i <= end_half; ++i)
        {
            string num{std::to_string(i)};
            uint64 length{num.size()};
            // int64 test{i * static_cast<int64>(std::pow(10, length)) + i};
            // if (test >= start && test <= end)
            // {
            //     result += test;
            // }
            for (auto j{1}; j <= length; ++j)
            {
                int64 test{0};
                int64 seq{std::stoll(num.substr(0, j))};
                for (auto x{j}; x <= length * 2 + 1; x += j)
                {
                    test = test * std::pow(10, j) + seq;
                    if (test >= start && test <= end)
                    {
                        if (invalid_ids.contains(test))
                        {
                            continue;
                        }
                        else
                        {
                            invalid_ids.insert(test);
                            // std::println("{}", test);
                            result += test;
                        }
                    }
                }
            }
        }

    }
    
    return result;
}

int main()
{
    fs::path parent_path{fs::current_path().parent_path()};
    fs::path test_file_path{parent_path / "tag2" / "test.txt"};
    fs::path input_file_path{parent_path / "tag2" / "input.txt"};
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
    // std::println("Test {}, correct is 1227775554", test_result_part_1);
    // std::println("Result: {}", result_part_1);

    auto test_result_part_2{part_2(test_data)};
    auto result_part_2{part_2(input_data)};
    std::println("Part 2:");
    std::println("Test {}, correct is 4174379265", test_result_part_2);
    std::println("Result: {}", result_part_2);

    return 0;
}
