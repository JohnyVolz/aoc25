#include <print>
#include <sstream>
#include <filesystem>
#include <cmath>

#include "../auxilary/types.hpp"
#include "../auxilary/errors.hpp"
#include "../auxilary/aoc_helper.cpp"

namespace fs = std::filesystem;

struct Point
{
    int64 x;
    int64 y;
    int64 z;
};

float64 distance(Point &a, Point &b)
{
    return std::sqrt(std::pow(b.x - a.x, 2) +
                     std::pow(b.y - a.y, 2) +
                     std::pow(b.z - a.z, 2));
}

pair<size_t, size_t> find_min_dist(vector<vector<float64>> &grid)
{
    float64 min_dist{std::numeric_limits<float64>::infinity()};
    size_t row{};
    size_t col{};
    for (auto i{0}; i < grid.size(); ++i)
    {
        for (auto j{i + 1}; j < grid.size(); ++j)
        {
            if (grid.at(i).at(j) < min_dist)
            {
                min_dist = grid.at(i).at(j);
                row = i;
                col = j;
            }
        }
    }
    pair<size_t, size_t> result{row, col};
    return result;
}

int64 part_1(string &data, int64 n_connection)
{
    vector<Point> points{};
    stringstream data_stream{data};
    string line{};
    while (std::getline(data_stream, line))
    {
        size_t comma1{line.find(",")};
        size_t comma2{line.find(",", comma1 + 1)};
        int64 x{std::stoll(line.substr(0, comma1))};
        int64 y{std::stoll(line.substr(comma1 + 1, comma2 - comma1))};
        int64 z{std::stoll(line.substr(comma2 + 1))};
        Point point{x, y, z};
        points.push_back(point);
    }

    vector<vector<float64>> grid;
    for (auto p1 : points)
    {
        vector<float64> row{};
        for (auto p2 : points)
        {
            if (p1.x == p2.x && p1.y == p2.y && p1.z == p2.z)
            {
                row.push_back(std::numeric_limits<float64>::infinity());
                continue;
            }
            row.push_back(distance(p1, p2));
        }
        grid.push_back(row);
    }

    for (auto row : grid)
    {
        for (auto e : row)
        {
            std::print(" {:7.4}", e);
        }
        std::println("");
    }

    pair<size_t, size_t> min_dist{find_min_dist(grid)};
    std::println("{},{}: {}", min_dist.first, min_dist.second, grid.at(min_dist.first).at(min_dist.second));
    // std::println("{}", std::distance(grid.begin(), std::min_element(grid.begin(), grid.end())));

    int64 result{0};
    return result;
}

int64 part_2(string &data)
{
    int64 result{0};

    return result;
}

int main()
{
    fs::path parent_path{fs::current_path().parent_path()};
    fs::path test_file_path{parent_path / "tag8" / "test.txt"};
    fs::path input_file_path{parent_path / "tag8" / "input.txt"};
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

    auto test_result_part_1{part_1(test_data, 10)};
    // auto result_part_1{part_1(input_data, 1000)};
    std::println("Part 1:");
    std::println("Test {}, correct is 40", test_result_part_1);
    // std::println("Result: {}", result_part_1);

    // auto test_result_part_2{part_2(test_data)};
    // auto result_part_2{part_2(input_data)};
    // std::println("Part 2:");
    // std::println("Test {}, correct is ...", test_result_part_2);
    // std::println("Result: {}", result_part_2);

    return 0;
}

// cmake --build . && ./tag8.out
