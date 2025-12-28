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
};

float64 distance(Point &a, Point &b)
{
    return (std::abs(a.x-b.x)+1)*(std::abs(a.y-b.y)+1);
}

std::tuple<size_t, size_t, float64> find_max_dist(vector<vector<float64>> &grid)
{
    float64 max_dist{0};
    size_t row{};
    size_t col{};
    for (auto i{0}; i < grid.size(); ++i)
    {
        for (auto j{i + 1}; j < grid.size(); ++j)
        {
            if (grid.at(i).at(j) > max_dist)
            {
                max_dist = grid.at(i).at(j);
                row = i;
                col = j;
            }
        }
    }
    std::tuple<size_t, size_t, float64> result{row, col, max_dist};
    return result;
}

vector<Point> parse_points(string &data)
{
    vector<Point> points{};
    stringstream data_stream{data};
    string line{};
    while (std::getline(data_stream, line))
    {
        size_t comma1{line.find(",")};
        size_t comma2{line.find(",", comma1 + 1)};
        int64 x{std::stoll(line.substr(0, comma1))};
        int64 y{std::stoll(line.substr(comma1 + 1))};
        Point point{x, y};
        points.push_back(point);
    }
    return points;
}

vector<Point> get_all_points(vector<Point> &points)
{
    vector<Point> all_points{};
    for (auto i{0}; i < points.size(); ++i)
    {   
        uint64 m;
        if (i == points.size() - 1)
        {
            m = 0;
        }
        else
        {
            m = i + 1;
        }
        Point& a{points.at(i)};
        Point& b{points.at(m)};
               
        if (a.x == b.x)
        {
            int64 y_min = a.y < b.y ? a.y : b.y;
            int64 y_max = a.y > b.y ? a.y : b.y;
            for (auto y{y_min+1}; y < y_max; y += 2)
            {
                Point p{a.x, y};
                all_points.push_back(p);
            }

        }
        if (a.y == b.y)
        {
            int64 x_min = a.x < b.x ? a.x : b.x;
            int64 x_max = a.x > b.x ? a.x : b.x; 
            for (auto x{x_min+1}; x < x_max; x += 2)
            {
                Point p{x, a.y};
                all_points.push_back(p);
            }
        }
        all_points.push_back(b);
    
    }
    return all_points;
}
     
bool point_inside(Point& a, Point& b, Point& t)
{
    int64 x_min = a.x < b.x ? a.x : b.x;
    int64 x_max = a.x > b.x ? a.x : b.x; 
    int64 y_min = a.y < b.y ? a.y : b.y;
    int64 y_max = a.y > b.y ? a.y : b.y; 
    if (t.x > x_min and t.x < x_max and t.y > y_min and t.y < y_max)
        return true;
    return false;
}


float64 part_1(string& data)
{
    vector<Point> points{parse_points(data)};

    vector<vector<float64>> grid;
    for (auto i{0}; i < points.size(); ++i)
    {
        vector<float64> row{};
        for (auto j{0}; j < points.size(); ++j)
        {
            if (i == j)
            {
                row.push_back(0);
                continue;
            }
            row.push_back(distance(points.at(i), points.at(j)));
        }
        grid.push_back(row);
    }

    auto res{find_max_dist(grid)};
    // std::println("{}", std::get<0>(res));
    // std::println("{}", std::get<1>(res));
    // std::println("{}", std::get<2>(res));

    float64 result{std::get<2>(res)};

    return result;
}

float64 part_2(string& data)
{
    vector<Point> points{parse_points(data)};
    vector<Point> all_points{get_all_points(points)};
    std::println("All points size: {}", all_points.size());

    vector<vector<float64>> grid;
    for (auto i{0}; i < points.size(); ++i)
    {
        vector<float64> row{};
        for (auto j{0}; j < points.size(); ++j)
        {
            if (i == j)
            {
                row.push_back(0);
                continue;
            }
            if (i == 1 and j==6)
            {
                auto a{0};
            }
            bool point_is_valide{true};
            for (auto n{0}; n < all_points.size(); ++n)
            {
                if (point_inside(points.at(i), points.at(j), all_points.at(n)))
                {
                    point_is_valide = false;
                    break;
                }
            }
            if (point_is_valide)
                row.push_back(distance(points.at(i), points.at(j)));
            else
                row.push_back(0);
        }
        grid.push_back(row);
    }

    auto res{find_max_dist(grid)};
    std::println("{}", std::get<0>(res));
    std::println("{}", std::get<1>(res));
    std::println("{}", std::get<2>(res));

    float64 result{std::get<2>(res)};

    return result;
}

int main()
{
    fs::path parent_path{fs::current_path().parent_path()};
    fs::path test_file_path{parent_path / "tag9" / "test.txt"};
    fs::path input_file_path{parent_path / "tag9" / "input.txt"};
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
    // std::println("Test {}, correct is 50", test_result_part_1);
    // std::println("Result: {}", result_part_1);

    auto test_result_part_2{part_2(test_data)};
    std::println("Part 2:");
    std::println("Test {}, correct is 24", test_result_part_2);
    auto result_part_2{part_2(input_data)};
    std::println("Result: {}", result_part_2);

    return 0;
}

// cmake --build . && ./tag9.out
