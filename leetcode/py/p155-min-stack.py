# LeetCode 155. Min Stack.


class MinStack:
    def __init__(self):
        self.stack = []
        self.smalls = []  # compact list of the smallest current value.

    def push(self, val: int) -> None:
        self.stack.append(val)
        if len(self.smalls) == 0 or val <= self.smalls[-1]:
            self.smalls.append(val)

    def pop(self) -> None:
        if self.smalls[-1] == self.stack[-1]:
            self.smalls.pop()
        self.stack.pop()

    def top(self) -> int:
        return self.stack[-1]

    def getMin(self) -> int:
        return self.smalls[-1]


class MinStack2:
    def __init__(self):
        self.stack = []
        self.smallest = None

    def push(self, val: int) -> None:
        self.stack.append(val)
        if self.smallest and val < self.smallest:
            self.smallest = val

    def pop(self) -> None:
        if self.smallest and self.smallest == self.stack[-1]:
            self.smallest = None
        self.stack.pop()

    def top(self) -> int:
        return self.stack[-1]

    def getMin(self) -> int:
        if not self.smallest:
            self.smallest = min(self.stack)
        return self.smallest


class MinStack3:
    def __init__(self):
        self.stack = []

    def push(self, val: int) -> None:
        self.stack.append(val)

    def pop(self) -> None:
        self.stack.pop()

    def top(self) -> int:
        return self.stack[-1]

    def getMin(self) -> int:
        return min(self.stack)


tests = (
    (
        ["MinStack", "push", "push", "push", "getMin", "pop", "top", "getMin"],
        [[], [-2], [0], [-3], [], [], [], []],
        [None, None, None, None, -3, None, 0, -2],
    ),
    (
        [
            "MinStack",
            "push",
            "push",
            "getMin",
            "getMin",
            "push",
            "getMin",
            "getMin",
            "top",
            "getMin",
            "pop",
            "push",
            "push",
            "getMin",
            "push",
            "pop",
            "top",
            "getMin",
            "pop",
        ],
        [
            [],
            [-10],
            [14],
            [],
            [],
            [-20],
            [],
            [],
            [],
            [],
            [],
            [10],
            [-7],
            [],
            [-7],
            [],
            [],
            [],
            [],
        ],
        [
            None,
            None,
            None,
            -10,
            -10,
            None,
            -20,
            -20,
            -20,
            -20,
            None,
            None,
            None,
            -10,
            None,
            None,
            -7,
            -10,
            None,
        ],
    ),
)

for ops, vals, exps in tests:
    minStack = MinStack()
    for op, val, exp in zip(ops, vals, exps):
        # print(f"{op}({val}), exp: {exp}")
        if op == "MinStack":
            pass
        elif op == "push":
            minStack.push(val[0])
        elif op == "pop":
            minStack.pop()
        elif op == "top":
            act = minStack.top()
            if exp != act:
                print(f"Fail: {op}() exp: {exp}, act: {act}")
        elif op == "getMin":
            act = minStack.getMin()
            if exp != act:
                print(f"Fail: {op}() exp: {exp}, act: {act}")
        else:
            raise RuntimeError(f"bad op: {op}")
