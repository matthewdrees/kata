class Solution:
    def isRobotBounded(self, instructions: str) -> bool:
        x = 0
        y = 0
        dir = 0  # 0: up, 1: right, 2: down, 3: left
        for instruction in instructions:
            if instruction == "G":
                if dir == 0:
                    y += 1
                elif dir == 1:
                    x += 1
                elif dir == 2:
                    y -= 1
                elif dir == 3:
                    x -= 1
                else:
                    assert False, f"bad direction: {dir}"
            elif instruction == "L":
                dir = (dir + 3) % 4
            elif instruction == "R":
                dir = (dir + 1) % 4
            else:
                assert False, f"bad instruction: {instruction}"
        if x == 0 and y == 0:
            return True
        if dir != 0:
            return True
        return False


if __name__ == "__main__":

    s = Solution()
    tests = (
        ("", True),
        ("G", False),
        ("R", True),
        ("L", True),
        ("LG", True),
        ("RG", True),
        ("GR", True),
        ("GL", True),
        ("GLLLL", False),
        ("GRRRR", False),
        ("GG", False),
        ("GGLLGG", True),
    )

    for test in tests:

        instructions = test[0]
        exp = test[1]
        ans = s.isRobotBounded(instructions)
        if exp != ans:
            print(f"FAIL. s: {instructions}, exp: {exp}, ans: {ans}")
