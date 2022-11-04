# LeetCode 43. Multiply Strings.
import array
import inspect


def multiply1(num: str, x: int, stage_num: int, a):
    stage_num = len(a) - stage_num - 1
    carry = 0
    for c in reversed(num):
        val = (ord(c) - 48) * x + a[stage_num] + carry
        carry, a[stage_num] = divmod(val, 10)
        stage_num -= 1

    while carry != 0:
        val = carry + a[stage_num]
        carry, a[stage_num] = divmod(val, 10)
        stage_num -= 1


def get_numstring_from_array(a):
    for i, x in enumerate(a):
        if x != 0:
            b = a[i:]
            for y in range(len(b)):
                b[y] += 48
            return b.tobytes().decode()
    return "0"


class Solution:
    def multiply(self, num1: str, num2: str) -> str:
        # Rules say you can't do this:
        # return str(int(num1) * int(num2))

        if len(num1) <= len(num2):
            longer_num = num1
            shorter_num = num2
        else:
            longer_num = num2
            shorter_num = num1
        a = array.array("b", [0] * (len(num1) + len(num2)))

        stage_num = 0
        for c in reversed(shorter_num):
            multiply1(longer_num, ord(c) - 48, stage_num, a)
            stage_num += 1

        return get_numstring_from_array(a)


def test_get_numstring_from_array():
    test_cases = (
        ([0], "0"),
        ([1], "1"),
        ([0, 1], "1"),
        ([7, 8, 9], "789"),
        ([7, 0, 9], "709"),
        ([0, 0, 7, 0, 9], "709"),
        ([0, 0, 7, 0, 9, 0], "7090"),
    )
    for l, exp in test_cases:
        a = array.array("b", l)
        act = get_numstring_from_array(a)
        if exp != act:
            print(
                f"{inspect.currentframe().f_code.co_name}, FAIL, a: {l}, exp: {exp}, act: {act}"
            )


def test_multiply1():
    test_cases = (
        # ([0, 0], "0", 3, 0, [0, 0]),
        # ([0, 0], "1", 3, 0, [0, 3]),
        # ([0, 0], "1", 3, 1, [3, 0]),
        # ([0, 1], "0", 3, 0, [0, 1]),
        # ([0, 1], "1", 0, 0, [0, 1]),
        # ([0, 1], "1", 3, 0, [0, 4]),
        # ([0, 1], "11", 3, 0, [3, 4]),
        # ([0, 0, 1], "51", 3, 0, [1, 5, 4]),
        ([0, 0, 0, 0, 0, 0], "123", 6, 0, [0, 0, 0, 7, 3, 8]),
        ([0, 0, 0, 7, 3, 8], "123", 5, 1, [0, 0, 6, 8, 8, 8]),
        ([0, 0, 6, 8, 8, 8], "123", 4, 2, [0, 5, 6, 0, 8, 8]),
    )
    for l, num, x, stage_num, exp in test_cases:
        a = array.array("b", l)
        multiply1(num, x, stage_num, a)
        ans = a.tolist()
        if exp != ans:
            print(
                f"{inspect.currentframe().f_code.co_name}, FAIL, num: {num}, x: {x}, stage_num: {stage_num}, exp: {exp}, ans: {ans}"
            )


def test_multiply():
    test_cases = (
        ("2", "3", "6"),
        ("123", "456", "56088"),
        ("456", "123", "56088"),
    )

    solution = Solution()
    for num1, num2, exp in test_cases:
        act = solution.multiply(num1, num2)
        if exp != act:
            print(
                f"{inspect.currentframe().f_code.co_name}, FAIL, num1: {num1}, num2: {num2}, exp: {exp}, act: {act}"
            )


if __name__ == "__main__":
    test_get_numstring_from_array()
    test_multiply1()
    test_multiply()
