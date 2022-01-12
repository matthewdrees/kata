# LeetCode 716. Max Stack.


class MaxStack:
    def __init__(self):
        self.l = []

    def push(self, x: int) -> None:
        self.l.append(x)

    def pop(self) -> int:
        return self.l.pop()

    def top(self) -> int:
        return self.l[-1]

    def peekMax(self) -> int:
        return max(self.l)

    def popMax(self) -> int:
        max_val = self.peekMax()
        self.l.reverse()
        i = self.l.index(max_val)
        self.l.reverse()
        return self.l.pop(len(self.l) - i - 1)


if __name__ == "__main__":
    stk = MaxStack()
    stk.push(5)
    if stk.l != [5]:
        print(f"Fail, exp: [5], act: {stk.l}")
    stk.push(1)
    if stk.l != [5, 1]:
        print(f"Fail, exp: [5, 1], act: {stk.l}")
    stk.push(5)
    if stk.l != [5, 1, 5]:
        print(f"Fail, exp: [5, 1, 5], act: {stk.l}")
    ret = stk.top()
    if ret != 5 or stk.l != [5, 1, 5]:
        print(f"Fail, exp: 5, [5, 1, 5], act: {ret}, {stk.l}")
    ret = stk.popMax()
    if ret != 5 or stk.l != [5, 1]:
        print(f"Fail, exp: 5, [5, 1], act: {ret}, {stk.l}")
    ret = stk.top()
    if ret != 1 or stk.l != [5, 1]:
        print(f"Fail, exp: 1, [5, 1], act: {ret}, {stk.l}")
    ret = stk.peekMax()
    if ret != 5 or stk.l != [5, 1]:
        print(f"Fail, exp: 5, [5, 1], act: {ret}, {stk.l}")
    ret = stk.pop()
    if ret != 1 or stk.l != [5]:
        print(f"Fail, exp: 1, [5], act: {ret}, {stk.l}")
    ret = stk.top()
    if ret != 5 or stk.l != [5]:
        print(f"Fail, exp: 5, [5], act: {ret}, {stk.l}")
