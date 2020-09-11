import pytest

def sparse_search(s, t, low, high):
    if low > high:
        return None
    mid = (low+high)//2
    if s[mid] == t:
        return mid
    if s[mid] == "":
        ret = sparse_search(s,t,low,mid-1)
        if ret is not None:
            return ret
        ret = sparse_search(s,t,mid+1,high)
        return ret
    if s[mid] < t:
        return sparse_search(s,t,mid+1,high)
    else:
        return sparse_search(s,t,low,mid-1)

@pytest.mark.parametrize("sorted_parse_string_list, target, index", [
    (["at", "", "", "","ball","","","cat","","","dat","",""], "ball", 4),
    (["at", "", "", "","ball","","","cat","","","dat","",""], "dog", None)
])
def test_sparse_search(sorted_parse_string_list, target, index):
    assert sparse_search(sorted_parse_string_list, target, 0, len(sorted_parse_string_list) - 1) == index
