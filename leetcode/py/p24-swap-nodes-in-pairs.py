# LeetCode p24. Swap Nodes in Pairs.
from typing import List

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def swapPairs(self, head: ListNode) -> ListNode:
        if head and head.next:
            a = head
            b = head.next
            a.next = b.next
            b.next = a
            head = b
            prev = a
            while prev.next and prev.next.next:
                a = prev.next
                b = a.next
                a.next = b.next
                b.next = a
                prev.next = b
                prev = a
        return head


def create_list(num_nodes):
    """Return a list with num_nodes numbered 1 - num_nodes."""
    head = None
    for x in range(num_nodes, 0, -1):
        head = ListNode(x, head)
    return head


def print_list(head):
    l = []
    while head:
        l.append(head.val)
        head = head.next
    print(l)


if __name__ == "__main__":
    s = Solution()

    for x in range(7):
        print_list(s.swapPairs(create_list(x)))
