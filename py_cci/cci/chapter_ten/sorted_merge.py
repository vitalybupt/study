import pytest

class sorted_array(list):
    def __init__(self, size, *args):
        list.__init__(self, *args)
        self.size = size
    def getsize(self):
        return self.size
    def insert(self, index, val):
        super(sorted_array, self).insert(index, val)
        if(self.pop() != None):
            raise StopIteration
        self.size += 1
    
        
def sort_merge(arrayA:sorted_array, arrayB:list) ->list:
    index = 0
    iterB = iter(arrayB)
    a = arrayA[index]
    b = next(iterB)
    try:
        while(True):
            if(a is None or b<=a):
                arrayA.insert(index, b)
                b = next(iterB)
                index += 1
            else:
                index += 1
                a = arrayA[index]
    except StopIteration:
        pass
    return arrayA
                

@pytest.mark.parametrize("arrayA, arrayB, expected", [
    (sorted_array(4, [2,4,8,9,None,None,None]), [1,5,11], [1,2,4,5,8,9,11]),
    (sorted_array(5, [1,2,3,13,15,None,None,None]), [1,5,11], [1,1,2,3,5,11,13,15]),
    (sorted_array(5, [1,2,3,13,15,16,None,None]), [17,20], [1,2,3,13,15,16,17,20]),
    (sorted_array(5, [13,15,16,None,None]), [1,2], [1,2,13,15,16]),
    (sorted_array(5, [1,2,3,13,15,16,None,None]), [17,20,23], [1,2,3,13,15,16,17,20])
])
def test_sorted_merge(arrayA, arrayB, expected):
    assert sort_merge(arrayA, arrayB) == expected

