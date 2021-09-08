from re import S
import pyperf
import random
import string


class Solution:
    def longestPalindrome(self, s: str) -> str:
        len_s = len(s)
        if len_s <= 1:
            return s
        i_longest = 0
        longest_length = 1
        i_end = len_s - 1
        i = 0
        while i < i_end:
            # Odd-length palendrome
            x = 1
            while True:
                if i - x >= 0 and i + x < len_s and s[i - x] == s[i + x]:
                    length = x * 2 + 1
                    if length > longest_length:
                        longest_length = length
                        i_longest = i
                        i_end = len_s - x
                    x += 1
                else:
                    break
            # Even-length palendrome
            x = 1
            while True:
                if i - x + 1 >= 0 and i + x < len_s and s[i - x + 1] == s[i + x]:
                    length = x * 2
                    if length > longest_length:
                        longest_length = length
                        i_longest = i
                        i_end = len_s - x
                    x += 1
                else:
                    break
            i += 1

        x = longest_length // 2
        start = i_longest - x
        if longest_length % 2 == 0:
            start += 1
        return s[start : i_longest + x + 1]


if __name__ == "__main__":

    s = Solution()
    tests = (
        ("", ""),
        ("babad", "bab"),
        ("adbab", "bab"),
        ("cbbd", "bb"),
        ("ccbd", "cc"),
        ("amanaplanacanalpanama", "amanaplanacanalpanama"),
        ("bbbbba", "bbbbb"),
        ("wwkew", "ww"),
        ("wkeww", "ww"),
        ("abcdefghijklmnopqrstuvwxyz", "a"),
    )

    for test in tests:

        str = test[0]
        exp = test[1]
        ans = s.longestPalindrome(str)
        if exp != ans:
            print(f"FAIL. str: {str}, exp: {exp}, ans: {ans}")

    # random_letters = []
    # for _ in range(1000):
    #    random_letters.append(random.choice(string.ascii_letters))
    # print("".join(random_letters))
    perf_str = "JFiAZYNSblRaBXiKkLGgAtGLexvorTdhZEBERdmRipoDcaqpVGEmfDeBgWqjDgwaWRkNrthvvHUHUQLgncBkfuIhtjYdqNxvuyFRIoZbgXEKJemqeCEqkKAgnlwwaxqmVhAjhNlPkSGlnPfRDLXwNhooClTPSrxpxgmaAUngTkOsTlXcltXnHAnimxzDYPDYRvTsDvORoIJiRkHtQvteTgMUAkjWqHLNUPchofaXRqdCvWXHYzYfOSiwaFUheFQHEuxKSmXIyjCCESrRVVOmLLUuowserGrfHkFycsbhPpyCOYWgJxDCVyDOrjuEQAaoVQyvuOBhWwVEWqmPJoIEtIdaJAaLCQTKwVNlqNQApTUiiiBTkhsSKhUkzXeEMYWYnZBgdaplMxUmoZUoxVxPPWkMvbjakAZYipnucjSfLUyUMEgEkMuUFSInBnlYLDbJzYNhWEuzKKXpliCAZzwFMKGOOsvrXrqmVxOZOvctJrgkRrmBAbTiEnVbniGCoKumLKzfCfarCoLaqzyxRDqgPbPwVCaCpracfhNImVXHZjjxvjnqLrarouVCBGNRYWKgjqbKJmtykgNNJLQOdRrhNCENvEFPmtHhzuPZZFItacGIUtqxbxOJlYcWmbbiJCKNfRweZhnsphOuqPOUbrjINEhpZxeqjyfAeOiIFiPpdSYaSzGIzZQntYyOkiZFZKxnYqAraczNCFGPHbxohcfCXinlIqDbIlBGIpzKDpJpHevlInCGMKgjuYTDMrIDplQDdEdfzpgRWEgLRYKBdbUzaeAuZwEqsbtuzwVaKFMwfVewSxRXEQRlzdWYHzJhxXUtqcAisjBcJUvqkcTIxGrOYFDvQpjnmYvNurkqTUNFvQaanQxxVpZMVDlRzdDwmkHDomFfFvvFEZcKtKuHHWPszQbGHUsNXuizrrKndvpcYREWQLStsfhgLouZcCLEWLcdXxowIFAPptjFCbMPePeAZsVgkMLGHQOvnjHEbzVK"
    runner = pyperf.Runner()
    runner.bench_func("s.longestPalindrome(perf_str)", s.longestPalindrome, perf_str)
    # for _ in range(100):
    #    print(s.longestPalindrome(perf_str))
