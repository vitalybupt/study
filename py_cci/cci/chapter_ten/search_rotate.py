import pytest

def search(s_l, target, low, high):
    if(low > high):
        return None

    middle = (low + high) // 2
    print("low ", low, " high ", high)
    if s_l[middle] == target:
        return middle

    if s_l[middle] < target:
        return search(s_l, target, middle + 1, high)
    elif s_l[middle] > target:
        return search(s_l, target, low, middle - 1)
    
def rotate_search(r_l, target, low, high):
    print("search ", target)
    if(r_l[low] < r_l[high]):
        return search(r_l, target, low, high)
    mid = (low + high) // 2
    if(target == r_l[mid]):
        return mid
    if(r_l[mid] > r_l[low] and r_l[mid] > r_l[high]):
        if(target < r_l[mid]):
            return search(r_l, target, low, mid - 1)
        else:
            return rotate_search(r_l, target, mid + 1, high)
    else:
        if(target < r_l[high]):
            return search(r_l, target, mid + 1, high)
        else:
            return rotate_search(r_l, target, low, mid - 1)
    
    
    
@pytest.mark.parametrize("rotated_list, target, index", [
    ([15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14], 5,  8),
    ([15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14], 10, 10),
    ([15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14], 15, 0),
    ([15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14], 19, 2),
])
def test_search_rotate(rotated_list, target, index):
    assert rotate_search(rotated_list, target, 0, len(rotated_list) - 1) == index
