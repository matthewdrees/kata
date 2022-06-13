# LeetCode 71. Simplify Path.


class Solution:
    def simplifyPath(self, path: str) -> str:
        path_parts = path.split("/")
        out_path_parts = []
        for path_part in path_parts:
            if not path_part or path_part == ".":
                continue
            if path_part == "..":
                if len(out_path_parts) > 0:
                    out_path_parts.pop()
            else:
                out_path_parts.append(path_part)

        return "/" + "/".join(out_path_parts)


if __name__ == "__main__":
    tests = (
        ("/home/", "/home"),
        ("/../", "/"),
        ("/home//foo/", "/home/foo"),
        ("/./../grr", "/grr"),
        ("/.../grr", "/.../grr"),
    )
    solution = Solution()
    for path, exp in tests:
        act = solution.simplifyPath(path)
        if exp != act:
            print(f"Fail. path: {path}, exp: {exp}, act: {act}")