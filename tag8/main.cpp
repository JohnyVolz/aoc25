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

vector<size_t> get_intersection(vector<size_t> &v1, vector<size_t> &v2)
{   
    vector<size_t> res{};
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    std::set_intersection(v1.begin(),v1.end(),v2.begin(), v2.end(),std::back_inserter(res));
    return res;
}

vector<size_t> get_union(vector<size_t> &v1, vector<size_t> &v2)
{   
    vector<size_t> res{};
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    std::set_union(v1.begin(),v1.end(),v2.begin(), v2.end(),std::back_inserter(res));
    return res;
}

bool contains(vector<size_t> &v, uint64 e)
{
    return std::find(v.begin(), v.end(), e) != v.end();
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
        int64 y{std::stoll(line.substr(comma1 + 1, comma2 - comma1))};
        int64 z{std::stoll(line.substr(comma2 + 1))};
        Point point{x, y, z};
        points.push_back(point);
    }
    return points;
}

vector<vector<float64>> get_distance_grid(vector<Point> &points)
{
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
    return grid;
}

int64 part_1(string &data, int64 n_connection)
{
    vector<Point> points{parse_points(data)};
    vector<vector<float64>> grid{get_distance_grid(points)};


    vector<vector<float64>> connection_grid(grid.size(), vector<float64>(grid.size(), 0));


    for (auto i{0}; i < n_connection; ++i)
    {
        pair<size_t, size_t> min_dist{find_min_dist(grid)};
        grid.at(min_dist.first).at(min_dist.second) = std::numeric_limits<float64>::infinity();
        grid.at(min_dist.second).at(min_dist.first) = std::numeric_limits<float64>::infinity();
        connection_grid.at(min_dist.first).at(min_dist.second) = 1;
        connection_grid.at(min_dist.second).at(min_dist.first) = 1;

    }

    std::map<size_t, vector<size_t>> connections_count{};
    for (auto i{0}; i < connection_grid.size(); ++i)
    {
        connections_count[i] = {};
    }
    for (auto i{0}; i < connection_grid.size(); ++i)
    {
        for (auto j{0}; j < connection_grid.size(); ++j)
        {   
            if (j==i || connection_grid.at(i).at(j) == 0)
            {
                continue;
            }

            auto connections{get_union(connections_count.at(i), connections_count.at(j))};
            if (!contains(connections, i))
            {
                connections.push_back(i);
            }
            if (!contains(connections, j))
            {
                connections.push_back(j);
            }
            bool changed{true};
            while (changed)
            {
                changed = false;
                for (auto c: connections)
                {
                    auto new_connections{get_union(connections, connections_count.at(c))};
                    if (new_connections != connections)
                    {
                        changed = true;
                        connections = new_connections;
                        break;
                    }
                }
            }

            for (auto c: connections)
            {
                connections_count.at(c) = connections;
            }
        }
    }
    // for (auto entry: connections_count)
    // {   
    //     std::print("{}:",entry.first);
    //     for (auto c: entry.second)
    //     {
    //         std::print(" {}", c);
    //     }
    //     std::println("");
    // }

    vector<vector<size_t>> constellations{};
    for (auto &entry: connections_count)
    {
        auto c{entry.second};
        if (c.size() == 0)
        {
            c = {entry.first};
        }
        bool found{false};
        for (auto &constellation : constellations)
        {
            if (c == constellation)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            constellations.push_back(c);
        }
    }

    // for (auto entry: constellations)
    // {   
    //     for (auto c: entry)
    //     {
    //         std::print(" {}", c);
    //     }
    //     std::println("");
    // }

    vector<size_t> num_connections{};
    for (auto &c: constellations)
    {
        num_connections.push_back(c.size());
    }
    // for (auto &c: num_connections)
    // {
    //     std::print("{} ", c);
    // }
    // std::println("");
    std::sort(num_connections.begin(), num_connections.end());
    // for (auto &c: num_connections)
    // {
    //     std::print("{} ", c);
    // }
    // std::println("");

    int64 result{1};
    for (auto i{0}; i < 3; ++i)
    {
        result *= num_connections.at(num_connections.size()-i-1);
        // std::println("{}", num_connections.at(num_connections.size()-i-1));
    }
    return result;
}

int64 part_2(string &data)
{ 
    int64 result{0};
    vector<Point> points{parse_points(data)};
    vector<vector<float64>> grid{get_distance_grid(points)};

    std::map<size_t, vector<size_t>> connections{};
    for (uint64 i{0}; i < grid.size(); ++i)
    {
        connections[i] = {i};
    }

    while (true)
    {
        pair<size_t, size_t> min_dist{find_min_dist(grid)};
        grid.at(min_dist.first).at(min_dist.second) = std::numeric_limits<float64>::infinity();
        grid.at(min_dist.second).at(min_dist.first) = std::numeric_limits<float64>::infinity();
        

        auto connection_union{get_union(connections.at(min_dist.first), connections.at(min_dist.second))};

        for (auto c: connection_union)
        {
            connections.at(c) = connection_union;
        }

        // for (auto entry: connections)
        // {   
        //     std::print("{}:",entry.first);
        //     for (auto c: entry.second)
        //     {
        //         std::print(" {}", c);
        //     }
        //     std::println("");
        // }
        bool all_connected{true};
        for (auto entry: connections)
        {
            if (entry.second.size() != grid.size())
            {
                all_connected = false;
                break;
            }
        }
        if (all_connected)
        {
            result = points.at(min_dist.first).x * points.at(min_dist.second).x;
            break;
        }
    }
    

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

    auto test_result_part_2{part_2(test_data)};
    auto result_part_2{part_2(input_data)};
    std::println("Part 2:");
    std::println("Test {}, correct is 25272", test_result_part_2);
    std::println("Result: {}", result_part_2);

    return 0;
}

// cmake --build . && ./tag8.out
