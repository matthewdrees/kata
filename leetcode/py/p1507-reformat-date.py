# LeetCode 1507. Reformat Date.


class Solution:
    def reformatDate(self, date: str) -> str:
        months = [
            "Jan",
            "Feb",
            "Mar",
            "Apr",
            "May",
            "Jun",
            "Jul",
            "Aug",
            "Sep",
            "Oct",
            "Nov",
            "Dec",
        ]
        day, month, year = date.split()
        new_month = months.index(month) + 1
        if day[1].isdigit():
            new_day = day[:2]
        else:
            new_day = "0" + day[0]
        return f"{year}-{new_month:02}-{new_day}"


tests = (
    ("20th Oct 2052", "2052-10-20"),
    ("6th Jun 1933", "1933-06-06"),
    ("26th May 1960", "1960-05-26"),
)

solution = Solution()
for date, exp in tests:
    act = solution.reformatDate(date)
    if exp != act:
        print(f"FAIL. date: {date}, exp: {exp}, act: {act}")
