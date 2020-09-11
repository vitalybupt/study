import pytest

class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None
    def __next__(self):
        if(self == None):
            raise stopIteration
        return self.next
    
#reverse_list 接收一个链表的头节点作为入参，返回reverse后的链表
def reverse_list(head):
    #终止条件：
    if(head.next == None):
        return head
    cur = head;
    new_end = cur.next
    #第一部分：将子链表逆序，这里要学会相信reverse_list虽然还没有写完，但它能完成
    #你设计它应完成的任务：接收头节点作入参，然后reverse后的链表。
    new_head = reverse_list(cur.next);
    #第二部分：将cur附在逆序后的子链表之后：
    new_end.next = cur
    return new_head

head = ListNode(0)
node = head
for i in range(5):
    node.next = ListNode(i)
    node = node.next

def test_reverse_list():
    new_head = reverse_list(head)
    assert new_head.val == 4
