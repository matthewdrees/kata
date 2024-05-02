// helper functions for leetcode problems.
#include <sstream>
#include <vector>

namespace leetcode {

template <typename T>
std::string to_string(const std::vector<T>& v)
{
    std::ostringstream oss;
    oss << '{';
    for (const auto& i : v) {
        oss << i << ',';
    }
    oss << "\b}"; // \b chomps the last comma.
    return oss.str();
}

template <typename T>
std::string to_string(const std::vector<std::vector<T>>& v)
{
    std::ostringstream oss;
    oss << '{';
    for (const auto& row : v) {
        oss << '{';
        for (const auto& x : row) {
            oss << x << ',';
        }
        oss << "\b},"; // \b chomps the last comma.
    }
    oss << "\b}"; // \b chomps the last comma.
    return oss.str();
}
}
