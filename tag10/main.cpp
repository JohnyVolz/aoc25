#include <print>
#include <sstream>
#include <filesystem>
#include <cmath>
#include <ranges>

#include "../auxilary/types.hpp"
#include "../auxilary/errors.hpp"
#include "../auxilary/aoc_helper.cpp"

namespace fs = std::filesystem;

class Machine
{
public:
    Machine() = delete;
    ~Machine() = default;  

    uint32 m_indicators{0};
    vector<uint32> m_buttons{};
    vector<vector<uint32>> m_buttons_num{};
    vector<uint32> m_joltage{};
    uint32 m_max_presses{0};

    Machine(string& data)
    {
        auto serparator_1{data.find(" ")};
        auto serparator_2{data.find("{")};
        string_view indicators_str{data.substr(1, serparator_1 - 2)};
        for (auto i{0}; i < indicators_str.size(); ++i)
        {
            m_indicators |= (indicators_str.at(i) == '#' ? (1 << i) : 0);
        }

        auto buttons_str = data.substr(serparator_1 + 1, serparator_2 - serparator_1 - 2);
        for (auto c : std::views::split(buttons_str, ' '))
        {   
            string_view button_sv{string_view(&*c.begin(), std::ranges::distance(c))};
            button_sv = button_sv.substr(1, button_sv.size() - 2);
            uint32 button{0};
            vector<uint32> button_nums{};
            for (auto n : std::views::split(button_sv, ','))
            {
                string ns{string(&*n.begin(), std::ranges::distance(n))};
                auto number{static_cast<uint32>(std::stoi(ns))};
                button |= (1 << number);
                button_nums.push_back(number);
            }
            m_buttons.push_back(button);
            m_buttons_num.push_back(button_nums);
        }

        auto joltage_str = data.substr(serparator_2 + 1, data.size() - serparator_2 - 2);
        for (auto c : std::views::split(joltage_str, ','))
        {  
            m_joltage.push_back(static_cast<uint32>(std::stoi(string(&*c.begin(), std::ranges::distance(c)))));
        }

        for (auto j: m_joltage)
        {
            m_max_presses += j;
        }
    }

    uint32 find_min_button_presses(this auto &self)
    {
        uint32 min_presses{255};
        if (self.m_indicators == 24)
            auto a{0};
        for (auto i{0}; i < self.m_buttons.size(); ++i)
        {
            if (self.m_buttons.at(i) == self.m_indicators)
                min_presses = 1;
            uint32 presses = self.press_button(i + 1, 1, self.m_buttons.at(i));
            if (presses < min_presses)
                min_presses = presses;
        }
        if (min_presses == 255)
            throw std::runtime_error("No solution found");
        return min_presses;
    }

    uint32 press_button(this auto &self, uint32 idx, uint32 presses, uint32 active)
    {   
        uint32 return_value{255};
        for (auto i{idx}; i < self.m_buttons.size(); ++i)
        {   
            auto temp_active{active xor self.m_buttons.at(i)};
            if (temp_active == self.m_indicators and presses + 1 < return_value)
                return_value = presses + 1;
            if (i < self.m_buttons.size())
            {
                uint32 temp_value{self.press_button(i + 1, presses + 1, temp_active)};
                if (temp_value < return_value)
                    return_value = temp_value;
            }
        }
        return return_value;
    }

    uint32 joltage_press(this auto& self, uint32 presses, vector<uint32> current_joltage)
    {
        uint32 return_value{std::numeric_limits<uint32>::max()};
        if (presses >= self.m_max_presses)
            return return_value;
        for (auto i{0}; i < self.m_buttons_num.size(); ++i)
        {
            auto button_numbers{self.m_buttons_num.at(i)};
            vector<uint32> temp_joltage{current_joltage};
            bool valid{true};
            for (auto number : button_numbers)
            {
                if (temp_joltage.at(number) > self.m_joltage.at(number))
                {
                    valid = false;
                    break;
                }
                temp_joltage.at(number) += 1;
            }
            if (!valid)
                continue;
            if (temp_joltage == self.m_joltage and presses + 1 < return_value)
            {
                return_value = presses + 1;
            }
            else
            {
                uint32 temp_value{self.joltage_press(presses + 1, temp_joltage)};
                if (temp_value < return_value)
                    return_value = temp_value;
            }

        }
        return return_value;
    }

    vector<uint32> get_max_presses(this auto& self, vector<uint32>& current_joltage)
    {
        vector<uint32> max_presses{};
        for (auto button: self.m_buttons_num)
        {   
            uint32 presses{UINT32_MAX};
            for (auto number: button)
            {
                if (self.m_joltage.at(number) - current_joltage.at(number) < presses 
                and self.m_joltage.at(number) - current_joltage.at(number) >= 0)
                {
                    presses = self.m_joltage.at(number) - current_joltage.at(number);
                }
            }
            if (presses == UINT32_MAX)
                presses = 0;
            max_presses.push_back(presses);
        }
        return max_presses;
    }
    
    void joltage_press_2(this auto& self, vector<uint32>& current_joltage)
    {   
        vector<uint32> max_presses{self.get_max_presses(current_joltage)};
        
        std::println("Max presses per button:");
        for (auto i{0}; i < max_presses.size(); ++i)
        {
            std::println("Button {} can be pressed max {} times", i, max_presses.at(i));
        }
    }
};

int64 part_1(vector<string> &data)
{   
    uint32 result{0};
    for (auto& line: data)
    {
        auto machine = Machine(line);
        auto res = machine.find_min_button_presses();
        result += res;
        std::println("{}", res);
    }

    return result;
}

int64 part_2(vector<string> &data)
{
    uint32 result{0};
    for (auto& line: data)
    {
        auto machine = Machine(line);
        vector<uint32> current_joltage(machine.m_joltage.size(), 0);
        // auto res{machine.joltage_press(0, current_joltage)};
        // std::println("{}", res);
        // result += res;
        machine.joltage_press_2(current_joltage);
    }

    return result;
}

int main()
{
    fs::path parent_path{fs::current_path().parent_path()};
    fs::path test_file_path{parent_path / "tag10" / "test.txt"};
    fs::path input_file_path{parent_path / "tag10" / "input.txt"};

    auto test_data{read_file_to_vector(test_file_path)};
    auto input_data{read_file_to_vector(input_file_path)};

    // auto test_result_part_1{part_1(test_data)};
    // std::println("Part 1:");
    // std::println("Test {}, correct is 7", test_result_part_1);
    // auto result_part_1{part_1(input_data)};
    // std::println("Result: {}", result_part_1);

    auto test_result_part_2{part_2(test_data)};
    std::println("Part 2:");
    std::println("Test {}, correct is 33", test_result_part_2);
    // auto result_part_2{part_2(input_data)};
    // std::println("Result: {}", result_part_2);

    return 0;
}

// cmake --build . && ./tag10.out
