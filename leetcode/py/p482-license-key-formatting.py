# LeetCode 482. License Key Formatting.


class Solution:
    def licenseKeyFormatting(self, s: str, k: int) -> str:
        s = s.upper()
        num_dashes = s.count("-")
        ik = (len(s) - num_dashes) % k
        if ik == 0:
            ik = k
        l = []
        for c in s:
            if c == "-":
                continue
            l.append(c)
            ik -= 1
            if ik == 0:
                l.append("-")
                ik = k
        if len(l) > 0 and l[-1] == "-":
            l.pop()
        return "".join(l)


if __name__ == "__main__":

    tests = (
        ("5F3Z-2e-9-w", 4, "5F3Z-2E9W"),
        ("5F3Z-2e-9-w5", 4, "5-F3Z2-E9W5"),
        ("b", 1, "B"),
        ("bb", 1, "B-B"),
        ("b-b", 2, "BB"),
        ("-", 1, ""),
        ("--a", 1, "A"),
        ("--", 1, ""),
        ("2-5g-3-J", 2, "2-5G-3J"),
        ("2-4A0r7-4k", 4, "24A0-R74K"),
    )
    solution = Solution()
    for s, k, exp in tests:
        ans = solution.licenseKeyFormatting(s, k)
        if exp != ans:
            print(f"FAIL. s: {s}, k: {k}, exp: {exp}, ans: {ans}")
