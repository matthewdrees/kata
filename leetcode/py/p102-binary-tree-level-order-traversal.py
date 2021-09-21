# LeetCode 102. Binary Tree Level Order Traversal.
from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def __init__(self):
        self.levels = []

    def levelOrderDepth(self, root, depth):
        if not root:
            return
        if len(self.levels) <= depth:
            self.levels.append([root.val])
        else:
            self.levels[depth].append(root.val)
        self.levelOrderDepth(root.left, depth + 1)
        self.levelOrderDepth(root.right, depth + 1)

    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        self.levels.clear()
        self.levelOrderDepth(root, 0)
        l = self.levels
        self.levels = []
        return l


if __name__ == "__main__":

    tests = (
        (
            TreeNode(3, TreeNode(9), TreeNode(20, TreeNode(15), TreeNode(7))),
            [[3], [9, 20], [15, 7]],
        ),
        (TreeNode(1), [[1]]),
        (None, []),
    )

    solution = Solution()

    for test in tests:
        root = test[0]
        exp = test[1]
        ans = solution.levelOrder(root)
        if exp != ans:
            print(f"Fail. exp: {exp}, ans: {ans}")
