#include <fstream>
#include <sstream>
// #include <iostream>

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