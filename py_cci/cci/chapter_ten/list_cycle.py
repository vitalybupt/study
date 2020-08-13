import pytest

class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None
    def __next__(self):
        if(self == None):
            raise stopIteration
        return self.next

        
class Solution:
    def detectCycle(self, head: ListNode) -> ListNode:
        if(head == None or next(head) == None):
            return None
        items = {}
        walker, runner = head, next(next(head))
        pos = 0
        while(runner != None and runner != walker):
            items[walker] = pos
            walker = next(walker)
            runner = next(next(runner))
            pos += 1
            
        if(runner == None):
            return None
        while(walker not in items.keys()):
            items[walker] = pos
            pos += 1
            walker = next(walker)
        return items[walker]
            
        
head = ListNode(0)
node = head
for i in range(5):
    node.next = ListNode(i)
    node = node.next
node.next = head.next

def test_list_cycle():
    solution = Solution()
    assert solution.detectCycle(head) == 1

