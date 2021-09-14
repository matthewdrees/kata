# LeetCode 1189. Maximum number of balloons.


class Solution:
    def maxNumberOfBalloons(self, text: str) -> int:
        l = [0, 0, 0, 0, 0]
        for c in text:
            if c == "b":
                l[0] += 1
            elif c == "a":
                l[1] += 1
            elif c == "l":
                l[2] += 1
            elif c == "o":
                l[3] += 1
            elif c == "n":
                l[4] += 1
        l[2] //= 2
        l[3] //= 2
        return min(l)


if __name__ == "__main__":

    solution = Solution()
    tests = (
        ("nlaebolko", 1),
        ("loonbalxballpoon", 2),
        ("leetcode", 0),
    )

    for test in tests:
        text = test[0]
        exp = test[1]
        ans = solution.maxNumberOfBalloons(text)
        if exp != ans:
            print(f"FAIL. text: {text}, exp: {exp}, ans: {ans}")
