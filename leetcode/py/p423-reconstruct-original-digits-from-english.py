# LeetCode 423. Reconstruct original digits from English.
import collections


class Solution:
    def originalDigits(self, s: str) -> str:
        num_0 = s.count("z")
        num_2 = s.count("w")
        num_4 = s.count("u")
        num_5 = s.count("f") - num_4
        num_6 = s.count("x")
        num_8 = s.count("g")
        l = []
        l.append("0" * num_0)
        l.append("1" * (s.count("o") - num_0 - num_2 - num_4))
        l.append("2" * num_2)
        l.append("3" * (s.count("h") - num_8))
        l.append("4" * num_4)
        l.append("5" * num_5)
        l.append("6" * num_6)
        l.append("7" * (s.count("s") - num_6))
        l.append("8" * num_8)
        l.append("9" * (s.count("i") - num_5 - num_6 - num_8))
        return "".join(l)


class Solution2:
    def originalDigits(self, s: str) -> str:
        counts = collections.Counter()
        for c in s:
            counts[c] += 1
        search_things = (
            ("z", "ro", "0"),
            ("w", "o", "2"),
            ("u", "for", "4"),
            ("o", "", "1"),
            ("r", "", "3"),
            ("f", "i", "5"),
            ("x", "si", "6"),
            ("s", "", "7"),
            ("g", "i", "8"),
            ("i", "", "9"),
        )
        l = []
        for st in search_things:
            count = counts[st[0]]
            if count > 0:
                l.extend([st[2]] * count)
                for c in st[1]:
                    counts[c] -= count
        l.sort()
        return "".join(l)


class Solution3:
    def originalDigits(self, s: str) -> str:
        counts = collections.Counter()
        for c in s:
            counts[c] += 1

        search_things = (
            ("z", "zero", "0"),
            ("w", "two", "2"),
            ("u", "four", "4"),
            ("o", "one", "1"),
            ("r", "three", "3"),
            ("f", "five", "5"),
            ("x", "six", "6"),
            ("s", "seven", "7"),
            ("g", "eight", "8"),
            ("i", "nine", "9"),
        )
        l = []
        for st in search_things:
            count = counts[st[0]]
            if count > 0:
                l.extend([st[2]] * count)
                for c in st[1]:
                    counts[c] -= count
        l.sort()
        return "".join(l)


if __name__ == "__main__":

    solution = Solution()
    tests = (
        ("owoztneoer", "012"),
        ("fviefuro", "45"),
        ("nineeightsevensixfivefourthreetwoonezero", "0123456789"),
        ("zero", "0"),
        ("zerozero", "00"),
        ("one", "1"),
        ("two", "2"),
        ("three", "3"),
        ("four", "4"),
        ("five", "5"),
        ("six", "6"),
        ("seven", "7"),
        ("eight", "8"),
        ("nine", "9"),
    )

    for test in tests:
        s = test[0]
        exp = test[1]
        ans = solution.originalDigits(s)
        if exp != ans:
            print(f"FAIL. s: {s}, exp: {exp}, ans: {ans}")
