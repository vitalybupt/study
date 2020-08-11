
import pytest

def sort_merge(arrayA, arrayB):
    workarray = []
    iterA = iter(arrayA)
    iterB = iter(arrayB)
    a = next(iterA)
    b = next(iterB)
    try:
        while(True):
            if(a is None or b<=a):
                workarray.append(b)
                b = next(iterB)
            else:
                workarray.append(a)
                a = next(iterA)
    except StopIteration:
        pass
    return workarray
                

@pytest.mark.parametrize("arrayA, arrayB, expected", [
    ([2,4,8,9,None,None,None], [1,5,11], [1,2,4,5,8,9,11]),
    ([1,2,3,13,15,None,None,None], [1,5,11], [1,1,2,3,5,11,13,15])
])
def test_sorted_merge(arrayA, arrayB, expected):
    assert sort_merge(arrayA, arrayB) == expected

