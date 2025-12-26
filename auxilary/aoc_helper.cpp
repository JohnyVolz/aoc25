#include <fstream>
#include <sstream>

#include "types.hpp"

namespace fs = std::filesystem;

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

string read_file(fs::path path)
{   
    fs::directory_entry input_file{path};
    if (!input_file.exists() || !input_file.is_regular_file())
    {
        throw std::runtime_error("file does not exist: " + path.string());
    }

    return read_file(path.string());
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

vector<string> read_file_to_vector(fs::path path)
{
    fs::directory_entry input_file{path};
    if (!input_file.exists() || !input_file.is_regular_file())
    {
        throw std::runtime_error("file does not exist: " + path.string());
    }
    
    return read_file_to_vector(path.string());
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
        for (char c : line)
        {
            line_v.push_back(string(1, c));
        }
        grid.push_back(line_v);
        line_v.clear();
    }
    return grid;
}

vector<vector<string>> read_file_to_grid(fs::path path)
{
    fs::directory_entry input_file{path};
    if (!input_file.exists() || !input_file.is_regular_file())
    {
        throw std::runtime_error("file does not exist: " + path.string());
    }
    
    return read_file_to_grid(path.string());
}

template <typename T>
bool v_contains(const std::vector<T> &vec, T element)
{
    if (std::find(vec.begin(), vec.end(), element) != vec.end())
    {
        return true;
    }
    return false;
}

template <typename T, typename S>
bool q_contains(const std::deque<T> &que, S &element)
{
    if (std::find(que.begin(), que.end(), element) != que.end())
    {
        return true;
    }
    return false;
}