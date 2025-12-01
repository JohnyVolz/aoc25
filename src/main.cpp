#include <print>
#include <fstream>

#include "types.hpp"


string readComplex64File(const str &path)
{
    std::ifstream in(path, std::ios::binary | std::ios::ate);
    if (!in)
    {
        throw std::runtime_error("Failed to open file: " + path);
    }

    std::streamsize fileSize = in.tellg();
    in.seekg(0, std::ios::beg);

    const std::size_t bytesPerComplex = 2 * sizeof(float32); // real + imag
    if (fileSize % bytesPerComplex != 0)
    {
        std::println(std::cerr, "Warning: file size is not a multiple of {} bytes. Last partial sample will be ignored.", bytesPerComplex);
    }

    std::size_t numComplex = static_cast<std::size_t>(fileSize) / bytesPerComplex;
    vector<float32> buffer;
    buffer.resize(numComplex * 2);
    if (!in.read(reinterpret_cast<char *>(buffer.data()), static_cast<std::streamsize>(buffer.size() * sizeof(float32))))
    {
        // If read fails but some data read, adjust numComplex accordingly
        std::streamsize bytesRead = in.gcount();
        numComplex = std::min<int32>(static_cast<int32>(bytesRead) / bytesPerComplex,
                                     2'000'000);
        buffer.resize(numComplex * 2);
    }
    out.reserve(numComplex);
    for (int32 i = 0; i < numComplex; ++i)
    {
        float64 re = buffer[2 * i];
        float64 im = buffer[2 * i + 1];
        out.emplace_back(re, im);
    }
}



int main()
{
    
    return 0;
}