# LeetCode 273. Integer to English Words
from typing import List

tens = [
    "",
    "",
    "Twenty",
    "Thirty",
    "Forty",
    "Fifty",
    "Sixty",
    "Seventy",
    "Eighty",
    "Ninety",
]

ones = [
    "",
    "One",
    "Two",
    "Three",
    "Four",
    "Five",
    "Six",
    "Seven",
    "Eight",
    "Nine",
    "Ten",
    "Eleven",
    "Twelve",
    "Thirteen",
    "Fourteen",
    "Fifteen",
    "Sixteen",
    "Seventeen",
    "Eighteen",
    "Nineteen",
]


def zero_to_thousand(num: int) -> List[str]:
    """Convert number 0 - 999 to list of words

    >>> zero_to_thousand(0)
    []
    >>> zero_to_thousand(1)
    ["One"]
    >>> zero_to_thousand(417)
    ["Four", "Hundred", "Seventeen"]
    """
    assert num >= 0 and num <= 999
    l = []
    if num >= 100:
        h, num = divmod(num, 100)
        l.append(ones[h])
        l.append("Hundred")
    if num >= 20:
        t, o = divmod(num, 10)
        l.append(tens[t])
        if o > 0:
            l.append(ones[o])
    elif num >= 1:
        l.append(ones[num])
    return l


class Solution:
    def numberToWords(self, num: int) -> str:
        if num == 0:
            return "Zero"
        l = []
        magnitudes = (
            (1_000_000_000, "Billion"),
            (1_000_000, "Million"),
            (1_000, "Thousand"),
        )
        for mag, s in magnitudes:
            if num >= mag:
                x, num = divmod(num, mag)
                l.extend(zero_to_thousand(x))
                l.append(s)
        if num > 0:
            l.extend(zero_to_thousand(num))
        return " ".join(l)


if __name__ == "__main__":
    tests = (
        (123, "One Hundred Twenty Three"),
        (12345, "Twelve Thousand Three Hundred Forty Five"),
        (
            1234567,
            "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven",
        ),
        (
            2147483647,
            "Two Billion One Hundred Forty Seven Million Four Hundred Eighty Three Thousand Six Hundred Forty Seven",
        ),
        (0, "Zero"),
        (1, "One"),
        (2, "Two"),
        (3, "Three"),
        (4, "Four"),
        (5, "Five"),
        (6, "Six"),
        (7, "Seven"),
        (8, "Eight"),
        (9, "Nine"),
        (10, "Ten"),
        (11, "Eleven"),
        (12, "Twelve"),
        (13, "Thirteen"),
        (14, "Fourteen"),
        (15, "Fifteen"),
        (16, "Sixteen"),
        (17, "Seventeen"),
        (18, "Eighteen"),
        (19, "Nineteen"),
        (20, "Twenty"),
        (100, "One Hundred"),
        (1_000, "One Thousand"),
        (1_000_000, "One Million"),
        (1_000_000_000, "One Billion"),
    )
    solution = Solution()
    for num, exp in tests:
        act = solution.numberToWords(num)
        if exp != act:
            print(f"Fail. num: {num}, exp: {exp}, act: '{act}'")
