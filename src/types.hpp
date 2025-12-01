#pragma once

#include <complex>
#include <string>
#include <vector>
#include <map>
#include <memory>

using int8 = std::int8_t;
using uint8 = std::uint8_t;
using int16 = std::int16_t;
using uint16 = std::uint16_t;
using int32 = std::int32_t;
using uint32 = std::uint32_t;
using int64 = std::int64_t;
using uint64 = std::uint64_t;

using size_t = std::size_t;

using float32 = float;
using float64 = double;
using float128 = long double;

using complex32 = std::complex<float32>;
using complex64 = std::complex<float64>;
using complex128 = std::complex<float128>;

using byte = std::byte;
using str = std::string;
using str_view = std::string_view;

template <typename T>
using optional = std::optional<T>;
template <typename T, std::size_t N>
using array = std::array<T, N>; // Fixed-size list of N elements of type T
template <typename T>
using vector = std::vector<T>; // Dynamic-size list of elements of type T
template <typename K, typename V>
using map = std::map<K, V>; // Dictionary with keys of type K and values of type V
template <typename T, typename S>
using pair = std::pair<T, S>; // Tuple of two elements of type T and S


// Use make_unique and make_shared to create instances of unique_ptr and shared_ptr
template <typename T>
using shared_ptr = std::shared_ptr<T>;
template <typename T>
using unique_ptr = std::unique_ptr<T>;