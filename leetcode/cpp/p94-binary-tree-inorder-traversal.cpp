// LeetCode 94. Binary tree inorder traversal.
#include <iostream>
#include <vector>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode()
        : val(0)
        , left(nullptr)
        , right(nullptr)
    {
    }
    TreeNode(int x)
        : val(x)
        , left(nullptr)
        , right(nullptr)
    {
    }
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x)
        , left(left)
        , right(right)
    {
    }
};

class Solution {
public:
    std::vector<int> inorderTraversal(TreeNode* root)
    {
        std::vector<int> v;
        if (root != nullptr) {
            const auto v_left = inorderTraversal(root->left);
            const auto v_right = inorderTraversal(root->right);
            v.reserve(1 + v_left.size() + v_right.size());
            v.insert(v.end(), v_left.begin(), v_left.end());
            v.push_back(root->val);
            v.insert(v.end(), v_right.begin(), v_right.end());
        }
        return v;
    }
};

int main()
{
    Solution solution;
    {
        std::vector<int> exp = { 1, 3, 2 };
        TreeNode* n3 = new TreeNode(3);
        TreeNode* n2 = new TreeNode(2, n3, nullptr);
        TreeNode* n1 = new TreeNode(1, nullptr, n2);
        const auto actual = solution.inorderTraversal(n1);
        if (exp != actual) {
            std::cerr << "FAIL: test 1\n";
        }
        delete n1;
        delete n2;
        delete n3;
    }
    {
        std::vector<int> exp = {};
        const auto actual = solution.inorderTraversal(nullptr);
        if (exp != actual) {
            std::cerr << "FAIL: test 2\n";
        }
    }
    {
        std::vector<int> exp = { 1 };
        TreeNode* n1 = new TreeNode(1);
        const auto actual = solution.inorderTraversal(n1);
        if (exp != actual) {
            std::cerr << "FAIL: test 3\n";
        }
        delete n1;
    }
    {
        std::vector<int> exp = { 2, 1 };
        TreeNode* n2 = new TreeNode(2);
        TreeNode* n1 = new TreeNode(1, n2, nullptr);
        const auto actual = solution.inorderTraversal(n1);
        if (exp != actual) {
            std::cerr << "FAIL: test 4\n";
        }
        delete n1;
        delete n2;
    }
    {
        std::vector<int> exp = { 1, 2 };
        TreeNode* n2 = new TreeNode(2);
        TreeNode* n1 = new TreeNode(1, nullptr, n2);
        const auto actual = solution.inorderTraversal(n1);
        if (exp != actual) {
            std::cerr << "FAIL: test 5\n";
        }
        delete n1;
        delete n2;
    }
    return 0;
}
