# LeetCode 380. Insert delete getrandom O(1).
import random


class RandomizedSet:
    def __init__(self):
        # These structures must stay in sync.
        self.l = []  # list of values, unsorted
        self.d = {}  # val -> l-index

    def insert(self, val: int) -> bool:
        if val in self.d:
            return False
        self.l.append(val)
        self.d[val] = len(self.l) - 1
        return True

    def remove(self, val: int) -> bool:
        if val in self.d:
            val_idx = self.d[val]
            swp_val = self.l.pop()
            if val_idx < len(self.l):
                self.l[val_idx] = swp_val
                self.d[swp_val] = val_idx
            del self.d[val]
            return True
        return False

    def getRandom(self) -> int:
        return random.choice(self.l)


def run_test(test):
    r = RandomizedSet()
    for command, val, exp in test:
        if command == "i":
            act = r.insert(val)
            if exp != act:
                print(
                    f"FAIL, test = {test}\ncommand: {command}, val: {val}, exp: {exp}, act: {act}"
                )
                return
        elif command == "r":
            act = r.remove(val)
            if exp != act:
                print(
                    f"FAIL, test = {test}\ncommand: {command}, val: {val}, exp: {exp}, act: {act}"
                )
                return
        elif command == "g":
            act = r.getRandom()
            if act not in exp:
                print(
                    f"FAIL, test = {test}\ncommand: {command}, val: {val}, exp: {exp}, act: {act}"
                )
                return


if __name__ == "__main__":

    tests = (
        (
            ("i", 1, True),
            ("r", 2, False),
            ("i", 2, True),
            ("g", 0, [1, 2]),
            ("r", 1, True),
            ("i", 2, False),
            ("g", 0, [2]),
        ),
        (
            ("r", 0, False),
            ("r", 0, False),
            ("i", 0, True),
            ("g", 0, [0]),
            ("r", 0, True),
            ("i", 0, True),
        ),
        (
            ("i", 3, True),
            ("i", 3, False),
            ("g", 0, [3]),
            ("g", 0, [3]),
            ("i", 1, True),
            ("r", 3, True),
            ("g", 0, [1]),
            ("g", 0, [1]),
            ("i", 0, True),
            ("r", 0, True),
        ),
    )
    for test in tests:
        run_test(test)
