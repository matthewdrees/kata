# LeetCode 94. Binary tree inorder traversal.
from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        l = []
        if not root:
            return l
        l.extend(self.inorderTraversal(root.left))
        l.append(root.val)
        l.extend(self.inorderTraversal(root.right))
        return l


if __name__ == "__main__":
    solution = Solution()
    tests = (
        (TreeNode(1, None, TreeNode(2, TreeNode(3))), [1, 3, 2]),
        (None, []),
        (TreeNode(1), [1]),
        (TreeNode(1, TreeNode(2)), [2, 1]),
        (TreeNode(1, None, TreeNode(2)), [1, 2]),
    )
    for test in tests:
        root = test[0]
        exp = test[1]
        ans = solution.inorderTraversal(root)
        if exp != ans:
            print(f"FAIL. exp: {exp}, ans: {ans}")
