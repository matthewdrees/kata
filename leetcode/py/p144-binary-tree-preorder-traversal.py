# LeetCode 144. Binary tree preorder traversal.
from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def preorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        l = []
        if not root:
            return l
        l.append(root.val)
        l.extend(self.preorderTraversal(root.left))
        l.extend(self.preorderTraversal(root.right))
        return l


if __name__ == "__main__":
    solution = Solution()
    tests = (
        (TreeNode(1, None, TreeNode(2, TreeNode(3))), [1, 2, 3]),
        (None, []),
        (TreeNode(1), [1]),
        (TreeNode(1, TreeNode(2)), [1, 2]),
        (TreeNode(1, None, TreeNode(2)), [1, 2]),
    )
    for test in tests:
        root = test[0]
        exp = test[1]
        ans = solution.preorderTraversal(root)
        if exp != ans:
            print(f"FAIL. exp: {exp}, ans: {ans}")
