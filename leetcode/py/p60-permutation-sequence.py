# LeetCode 60. Permutation Sequence.

def factorial(n):
    facts = (
        0,
        1,
        2,
        6,
        24,
        120,
        720,
        5040,
        40320,
        362880
    )
    return facts[n]

class Solution:
    def getPermutation(self, n: int, k: int) -> str:
        assert n>= 1 and n <= 9
        assert k >= 1 and k <= factorial(9)
        k -= 1
        l = [str(x) for x in range(1, n+1)]
        ans = []
        for i in range(n-1, 0, -1):
            div = factorial(i)
            idx, k = divmod(k, div)
            ans.append(l.pop(idx))
        ans.append(l[0])
        return "".join(ans)


test_cases = (
    (1, 1, "1"),
        ( 2, 1, "12" ),
        ( 2, 2, "21" ),
        ( 3, 1, "123" ),
        ( 3, 2, "132" ),
        ( 3, 3, "213" ),
        ( 3, 4, "231" ),
        ( 3, 5, "312" ),
        ( 3, 6, "321" ),
        ( 4, 1, "1234" ),
        ( 4, 2, "1243" ),
        ( 4, 9, "2314" ),
        ( 4, 24, "4321" ),
        ( 5, 1, "12345" ),
        ( 5, 120, "54321" ),
        ( 6, 1, "123456" ),
        ( 6, 720, "654321" ),
        ( 7, 1, "1234567" ),
        ( 7, 5040, "7654321" ),
        ( 8, 1, "12345678" ),
        ( 8, 40320, "87654321" ),
        ( 9, 1, "123456789" ),
        ( 9, 2, "123456798" ),
        ( 9, 362880, "987654321" ),
)

solution = Solution()
for n, k, exp in test_cases:
    act = solution.getPermutation(n, k)
    if exp != act:
        print(f"fail, n: {n}, k: {k}, exp: {exp}, act: {act}")
