// LeetCode 71. Simplify Path.
#include <algorithm>
#include <iostream>
#include <stack>

class Solution {
public:
    std::string simplifyPath(std::string path)
    {
        std::stack<std::string::iterator> slash_iters;
        auto path_end = path.end();
        auto cur = path.begin();
        while (true) {
            auto next = std::find(cur + 1, path_end, '/');
            const auto path_part_size = next - cur;
            if (path_part_size == 1 || (path_part_size == 2 && (*(cur + 1) == '.'))) {
                path_end = std::rotate(cur, next, path_end);
            } else if (path_part_size == 3 && *(cur + 1) == '.' && *(cur + 2) == '.') {
                if (!slash_iters.empty()) {
                    cur = slash_iters.top();
                    slash_iters.pop();
                }
                path_end = std::rotate(cur, next, path_end);
            } else {
                slash_iters.push(cur);
                cur = next;
            }
            if (cur == path_end) {
                break;
            }
        }
        const auto new_size = static_cast<size_t>(path_end - path.begin());
        if (new_size == 0) {
            path = "/";
        } else {
            path.resize(new_size);
        }
        return path;
    }
};

int main(int argc, char* argv[])
{
    struct TestCase {
        std::string path;
        std::string exp;
    };
    const TestCase testCases[] = {
        { "/", "/" },
        { "/.", "/" },
        { "/../", "/" },
        { "/home/", "/home" },
        { "/home//foo/", "/home/foo" },
        { "/home/./../grr/", "/grr" },
        { "/home/../../grr/", "/grr" },
        { "/a/b/c/../..", "/a" },
        { "/a/b/c/../../d", "/a/d" },
        { "/a/b/c/../../../d", "/d" },
        { "/a/b/c/../../../../d", "/d" },
        { "/.../grr/", "/.../grr" },
    };

    Solution solution;
    for (const auto& tc : testCases) {
        const auto ans = solution.simplifyPath(tc.path);
        if (tc.exp != ans) {
            std::cout << "FAIL. path: \"" << tc.path
                      << "\", exp: " << tc.exp
                      << ", ans: " << ans << "\n";
        }
    }
    return 0;
}
