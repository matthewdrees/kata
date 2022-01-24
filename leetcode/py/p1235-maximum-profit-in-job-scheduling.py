# LeetCode 1235. Maximum profit in job scheduling.
import bisect
from typing import List


class Job2:
    """Job end time and profit, that compares by end time for bisect.

    LeetCode python3 is currently v3.9. With v3.10 we get a key function for
    bisect calls that can clean this code up.
    """

    def __init__(self, end_time, profit):
        self.end_time = end_time
        self.profit = profit

    def __lt__(self, other):
        return self.end_time < other.end_time

    def __gt__(self, other):
        return self.end_time > other.end_time


class Solution:
    def jobScheduling(
        self, startTime: List[int], endTime: List[int], profit: List[int]
    ) -> int:
        jobs = list(zip(startTime, endTime, profit))
        jobs.sort(key=lambda x: x[0])  # Sort by startTime.

        active_jobs = []  # list of Job2, that will use end time for bisect comparison.
        max_profit = 0
        for start_time, end_time, job_profit in jobs:
            # Remove finished jobs from the front of the list, by comparing the
            # new job start time to the active job end times.
            active_jobs = active_jobs[bisect.bisect(active_jobs, Job2(start_time, 0)) :]

            # Add job to active_jobs, sorted by endTime.
            bisect.insort(active_jobs, Job2(end_time, job_profit))

            max_profit = max(max_profit, sum([j.profit for j in active_jobs]))

        return max_profit


if __name__ == "__main__":

    solution = Solution()
    tests = (
        # ([1, 2, 3, 3], [3, 4, 5, 6], [50, 10, 40, 70], 120),
        ([1, 2, 3, 4, 6], [3, 5, 10, 6, 9], [20, 20, 100, 70, 60], 150),
        ([1, 1, 1], [2, 3, 4], [5, 6, 4], 6),
    )

    for startTime, endTime, profit, exp in tests:
        ans = solution.jobScheduling(startTime, endTime, profit)
        if exp != ans:
            print(
                f"FAIL. startTime: {startTime}, endTime: {endTime}, profit: {profit}, exp: {exp}, ans: {ans}"
            )
