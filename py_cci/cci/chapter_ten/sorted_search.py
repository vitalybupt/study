import pytest

class Listy(list):
    def __init__(self, *args):
        list.__init__(self, *args)
    def at(self, i):
        if(i < len(self)):
            return self[i]
        return -1
def binary_search(listy, value, start, end):
    if(start > end):
        print("here ", value, " ", start, " ",end)
        return -1
    mid = (start + end) // 2
    if(listy.at(mid) == value):
        return mid
    elif(listy.at(mid) < value):
        return binary_search(listy, value, mid+1, end)
    else:
        return binary_search(listy, value, start, mid-1)
    
def sorted_search(listy, value, start):
    if(listy.at(start) == -1):
        return -1
    elif(listy.at(start) == value):
        return start
    guess_pos = start + value
    guess_value = listy.at(guess_pos)
    while guess_value == -1:
        guess_pos = (start + guess_pos) // 2
        guess_value = listy.at(guess_pos)
    if(guess_value == value):
        return guess_pos
    elif(guess_value > value):
        return binary_search(listy, value, start, guess_pos-1)
    else:
        return sorted_search(listy, value, guess_pos+1)

@pytest.mark.parametrize("listy, value, pos", [
    (Listy((1,2,4,4,6,9,12)), 2, 1),
    (Listy((1,2,4,4,6,9,12)), 6, 4),
    (Listy((1,2,4,4,6,9,12)), 4, 2),
    (Listy((1,2,4,4,6,9,12)), 20, -1)
])
def test_sorted_search(listy, value, pos):
    assert sorted_search(listy, value, 0) == pos
