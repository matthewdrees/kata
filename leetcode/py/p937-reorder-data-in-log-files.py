# LeetCode 937. Reorder data in log files.
import functools
from typing import List


class LogEntry:
    def __init__(self, log_entry):
        self.log_entry = log_entry
        i = log_entry.index(" ")
        self.is_digit = log_entry[i + 1].isdigit()
        if not self.is_digit:
            self.id = log_entry[:i]
            self.contents = log_entry[i + 1 :]

    def __lt__(self, other):
        if self.is_digit:
            return False
        if other.is_digit:
            return True
        else:  # both are letter logs.
            # First sort by contents.
            if self.contents == other.contents:
                # If contents are the same, sort by identifiers.
                return self.id < other.id
            else:
                return self.contents < other.contents


class Solution:
    def reorderLogFiles(self, logs: List[str]) -> List[str]:
        log_entries = [LogEntry(s) for s in logs]
        log_entries.sort()
        return [l.log_entry for l in log_entries]


if __name__ == "__main__":

    solution = Solution()
    tests = (
        (
            [
                "dig1 8 1 5 1",
                "let1 art can",
                "dig2 3 6",
                "let2 own kit dig",
                "let3 art zero",
            ],
            [
                "let1 art can",
                "let3 art zero",
                "let2 own kit dig",
                "dig1 8 1 5 1",
                "dig2 3 6",
            ],
        ),
        (
            ["a1 9 2 3 1", "g1 act car", "zo4 4 7", "ab1 off key dog", "a8 act zoo"],
            ["g1 act car", "a8 act zoo", "ab1 off key dog", "a1 9 2 3 1", "zo4 4 7"],
        ),
    )

    for test in tests:
        logs = test[0]
        exp = test[1]
        ans = solution.reorderLogFiles(logs)
        if exp != ans:
            print(f"FAIL. logs: {logs}\nexp: {exp}\nans: {ans}")
