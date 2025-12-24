#include <print>
#include <sstream>
#include <filesystem>
#include <cmath>

#include "../auxilary/types.hpp"
#include "../auxilary/errors.hpp"
#include "../auxilary/aoc_helper.cpp"

namespace fs = std::filesystem;

int64 part_1(string &data)
{
    map<string, vector<string>> devices;
    stringstream data_stream{data};
    string line{};
    while (std::getline(data_stream, line))
    {
        size_t collon{line.find(":")};
        size_t space{line.find(" ")};
        vector<string> connections{};
        while (space != string::npos)
        {
            connections.push_back(line.substr(space + 1, 3));
            space = line.find(" ", space + 1);
        }
        devices[line.substr(0, 3)] = connections;
        // std::println("{}, {}", collon, space);
    }
    // for (auto d : devices)
    // {
    //     std::print("{} : ", d.first);
    //     for (auto c : d.second)
    //     {
    //         std::print("{} ", c);
    //     }
    //     std::println("");
    // }

    set<vector<string>> visited_paths{};
    deque<string> que{};
    for (auto &path : devices.at("you"))
    {
        que.push_back(path);
        vector<string> c{"you", path};
        visited_paths.insert(c);
    }

    while (!que.empty())
    {
        set<vector<string>> paths_to_remove;
        set<vector<string>> new_paths;
        for (auto &visited_path : visited_paths)
        {
            if (visited_path.back() == que.front())
            {
                paths_to_remove.insert(visited_path);
                for (auto &p : devices.at(que.front()))
                {
                    if (v_contains(visited_path, p))
                        continue;
                    vector<string> new_p{visited_path};
                    new_p.push_back(p);
                    new_paths.insert(new_p);
                    if (p != "out" && !q_contains(que, p))
                    {
                        que.push_back(p);
                    }
                }
            }
        }
        for (auto &path : paths_to_remove)
        {
            visited_paths.erase(path);
        }
        for (auto &path : new_paths)
        {
            visited_paths.insert(path);
        }
        que.pop_front();
    }

    int64 result{0};
    for (auto &path : visited_paths)
    {
        if (path.back() == "out")
        {
            result++;
        }
    }

    return result;
}

uint64 find_path_count(const map<string, vector<string>> &devices, string start, string end)
{
    set<vector<string>> visited_paths{};
    deque<string> que{};
    for (auto &path : devices.at(start))
    {
        que.push_back(path);
        vector<string> c{start, path};
        visited_paths.insert(c);
    }

    while (!que.empty() && visited_paths.size() < 1000000)
    {
        set<vector<string>> paths_to_remove;
        set<vector<string>> new_paths;
        for (auto &visited_path : visited_paths)
        {
            if (visited_path.back() == que.front())
            {
                paths_to_remove.insert(visited_path);
                for (auto &p : devices.at(que.front()))
                {
                    if (v_contains(visited_path, p))
                        continue;
                    vector<string> new_p{visited_path};
                    new_p.push_back(p);
                    new_paths.insert(new_p);
                    if (p != end && !q_contains(que, p))
                    {
                        que.push_back(p);
                    }
                }
            }
        }
        for (auto &path : paths_to_remove)
        {
            visited_paths.erase(path);
        }
        for (auto &path : new_paths)
        {
            visited_paths.insert(path);
        }
        que.pop_front();
    }
    if (visited_paths.size() >= 1000000)
    {
        throw std::runtime_error("too many paths, increase limit");
    }

    uint64 path_count{visited_paths.size()};
    return path_count;
}

uint64 find_path_count_2(
    const map<string, vector<string>> &devices,
    map<string, uint64> &count,
    string start,
    string end)
{
    deque<string> que{start};
    while (!que.empty())
    {
        string node{que.front()};
        que.pop_front();

        bool unfinished_parents{false};
        for (auto &[name, connections] : devices)
        {
            if (v_contains(connections, node) && !count.contains(name))
            {
                unfinished_parents = true;
                break;
            }
        }
        if (unfinished_parents)
        {
            que.push_back(node);
            continue;
        }
        uint64 parents{0};
        for (auto &[name, connections] : devices)
        {
            if (v_contains(connections, node))
            {
                parents += count.at(name);
            }
        }
        if (parents == 0)
            parents = 1;
        count.insert({node, parents});
        if (node == end)
            continue;
        for (auto &c : devices.at(node))
        {
            if (q_contains(que, c))
                continue;
            que.push_back(c);
        }
    }

    uint64 result{count.at(end)};
    return result;
}

uint64 part_2(string &data)
{
    map<string, vector<string>> devices;
    stringstream data_stream{data};
    string line{};
    while (std::getline(data_stream, line))
    {
        size_t collon{line.find(":")};
        size_t space{line.find(" ")};
        vector<string> connections{};
        while (space != string::npos)
        {
            connections.push_back(line.substr(space + 1, 3));
            space = line.find(" ", space + 1);
        }
        devices[line.substr(0, 3)] = connections;
    }

    map<string, uint64> count{};
    uint64 svr_fft{find_path_count_2(devices, count, "svr", "out")};
    std::println("{} -> 7572", svr_fft);
    // uint64 fft_dac{find_path_count(devices, "fft", "dac")};
    // std::println("{}", fft_dac);
    // uint64 dac_out{find_path_count_2(devices, count, "dac", "out")};
    // std::println("{} -> 8216", dac_out);

    uint64 result{svr_fft};

    return result;
}

int main()
{
    fs::path parent_path{fs::current_path().parent_path()};
    fs::path test_file_path{parent_path / "tag11" / "test.txt"};
    fs::path test_file_2_path{parent_path / "tag11" / "test_2.txt"};
    fs::path input_file_path{parent_path / "tag11" / "input_m.txt"};
    fs::directory_entry test_file{test_file_path};
    fs::directory_entry test_file_2{test_file_2_path};
    fs::directory_entry input_file{input_file_path};
    if (!test_file.exists() || !test_file.is_regular_file())
    {
        throw std::runtime_error("file does not exist: " + test_file_path.string());
    }
    if (!test_file_2.exists() || !test_file_2.is_regular_file())
    {
        throw std::runtime_error("file does not exist: " + test_file_2_path.string());
    }
    if (!input_file.exists() || !input_file.is_regular_file())
    {
        throw std::runtime_error("file does not exist: " + input_file_path.string());
    }

    auto test_data{read_file(test_file.path().string())};
    auto test_2_data{read_file(test_file_2.path().string())};
    auto input_data{read_file(input_file.path().string())};

    // auto test_result_part_1{part_1(test_data)};
    // std::println("Part 1:");
    // std::println("Test {}, correct is 5", test_result_part_1);
    // auto result_part_1{part_1(input_data)};
    // std::println("Result: {}", result_part_1);

    // auto test_result_part_2{part_2(test_2_data)};
    // std::println("Part 2:");
    // std::println("Test {}, correct is 2", test_result_part_2);
    auto result_part_2{part_2(input_data)};
    std::println("Result: {}, correct is 517315308154944", result_part_2);

    return 0;
}

// cmake --build . && ./tag11.out
