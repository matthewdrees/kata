# LeetCode 811. Subdomain visit count.
from typing import List
import collections


class Solution:
    def subdomainVisits(self, cpdomains: List[str]) -> List[str]:
        d = collections.Counter()
        for cpdomain in cpdomains:
            count, domain = cpdomain.split(" ")
            count = int(count)
            while True:
                d[domain] += count
                idx = domain.find(".")
                if idx < 0:
                    break
                domain = domain[idx + 1 :]
        l = []
        for domain, count in d.items():
            l.append(f"{count} {domain}")
        return l


if __name__ == "__main__":

    solution = Solution()
    tests = (
        (
            ["9001 discuss.leetcode.com"],
            ["9001 leetcode.com", "9001 discuss.leetcode.com", "9001 com"],
        ),
        (
            ["900 google.mail.com", "50 yahoo.com", "1 intel.mail.com", "5 wiki.org"],
            [
                "901 mail.com",
                "50 yahoo.com",
                "900 google.mail.com",
                "5 wiki.org",
                "5 org",
                "1 intel.mail.com",
                "951 com",
            ],
        ),
    )

    for test in tests:
        cpdomains = test[0]
        exp = sorted(test[1])
        ans = solution.subdomainVisits(cpdomains)
        ans.sort()
        if exp != ans:
            print(f"FAIL. cpdomains: {cpdomains}\n exp: {exp}\n ans: {ans}")
