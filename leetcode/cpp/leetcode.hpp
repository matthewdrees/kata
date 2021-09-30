// helper functions for leetcode problems.
#include <sstream>
#include <vector>

namespace leetcode {

template <typename T>
std::string to_string(const std::vector<T>& v)
{
    std::ostringstream oss;
    oss << '{';
    for (const auto i : v) {
        oss << i << ',';
    }
    oss << "\b}"; // \b chomps the last comma.
    return oss.str();
}

}
