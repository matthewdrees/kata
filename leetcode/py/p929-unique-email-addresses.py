# LeetCode 929. Unique email addresses.
from typing import List


class Solution:
    def numUniqueEmails(self, emails: List[str]) -> int:
        unique_emails = set()
        for email in emails:
            local_name, domain_name = email.split("@")
            plus_index = local_name.find("+")
            if plus_index >= 0:
                local_name = local_name[0:plus_index]
            local_name = local_name.replace(".", "")
            unique_emails.add(f"{local_name}@{domain_name}")
        return len(unique_emails)


if __name__ == "__main__":
    solution = Solution()
    tests = (
        ([], 0),
        (["m.y+name@email.com"], 1),
        (
            [
                "test.email+alex@leetcode.com",
                "test.e.mail+bob.cathy@leetcode.com",
                "testemail+david@lee.tcode.com",
            ],
            2,
        ),
        (["a@leetcode.com", "b@leetcode.com", "c@leetcode.com"], 3),
    )
    for test in tests:
        emails = test[0]
        exp = test[1]
        ans = solution.numUniqueEmails(emails)
        if exp != ans:
            print(f"FAIL. emails: {emails}, exp: {exp}, ans: {ans}")
