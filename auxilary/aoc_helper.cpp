#include <fstream>
#include <sstream>

#include "types.hpp"

string read_file(string path)
{
    std::ifstream in(path);
    if (!in)
    {
        throw std::runtime_error("failed to open file: " + string(path));
    }
    std::ostringstream oss;
    oss << in.rdbuf();
    return oss.str();
}

vector<string> read_file_to_vector(string path)
{
    std::ifstream in(path);
    if (!in)
    {
        throw std::runtime_error("failed to open file: " + string(path));
    }
    vector<string> lines;
    string line;
    while (std::getline(in, line))
    {
        lines.push_back(line);
    }
    return lines;
}

vector<vector<string>> read_file_to_grid(string path)
{
    std::ifstream in(path);
    if (!in)
    {
        throw std::runtime_error("failed to open file: " + string(path));
    }
    vector<vector<string>> grid;
    vector<string> line_v;
    string line;
    while (std::getline(in, line))
    {   
        for (char c: line)
        {
            line_v.push_back(string(1, c));
        }
        grid.push_back(line_v);
        line_v.clear();

    }
    return grid;
}