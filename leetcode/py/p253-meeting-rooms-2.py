# LeetCode 253. Meeting Rooms 2
import bisect
from typing import List


class Solution:
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        # Sort by start time
        intervals.sort(key=lambda interval: interval[0])

        l = []  # list of active meeting end times
        max_num_meeting_rooms = 0
        for start_time, end_time in intervals:
            # Remove finished meetings from the list.
            l = l[bisect.bisect(l, start_time) :]

            # Add new meeting time in sorted order.
            l.insert(bisect.bisect(l, end_time), end_time)

            if len(l) > max_num_meeting_rooms:
                max_num_meeting_rooms = len(l)
        return max_num_meeting_rooms


if __name__ == "__main__":

    solution = Solution()
    tests = (
        ([[0, 1]], 1),
        ([[0, 30], [5, 10], [15, 20]], 2),
        ([[7, 10], [2, 4]], 1),
        ([[1, 2], [1, 2]], 2),
        ([[1, 2], [1, 2], [1, 2]], 3),
        ([[1, 2], [2, 3]], 1),
        ([[1, 5], [2, 5], [3, 5], [4, 5]], 4),
    )
    for test in tests:
        intervals = test[0]
        exp = test[1]
        ans = solution.meetingRooms(intervals)
        if exp != ans:
            print(f"FAIL. intervals: {intervals}, exp: {exp}, ans: {ans}")
