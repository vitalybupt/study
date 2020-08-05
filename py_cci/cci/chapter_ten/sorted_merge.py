def sort_merge(arrayA, arrayB):
    workarray = [None,]*len(arrayA)
    for(indexA, valueA in enumerate(arrayA)):
        for(indexB, valueB in enumerate(arrayB)):
            if(valueB <= valueA):
                workarray.append(valueB)
        workarray.append(valueA)
    return workarray
                

@pytest.mark.parametrize("arrayA, arrayB, expected", [
    ([2,4,8,9,None,None,None], [1,5,11], [1,2,4,5,8,9,11])
])
def test_sorted_merge(arrayA, arrayB, expected):
    assert sort_merge(arrayA, arrayB) == expected
    assert False
