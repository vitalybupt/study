import pytest

def group_anagrams(strings):
    dict = {}
    sorted_anagrams = []
    for s in strings:
        key = "".join(sorted(s))
        if key in dict:
            dict[key].append(s)
        else:
            dict[key] = [s]
    for groups in dict.values():
        for anagram in groups:
            sorted_anagrams.append(anagram)
    return sorted_anagrams
        
@pytest.mark.parametrize("strings, expected", [
    (["aba", "cbd", "baa", "bcd"], ["aba", "baa", "cbd", "bcd"]),
    (["zjw", "wmj", "jwz", "mjw"], ["zjw", "jwz", "wmj", "mjw"])
])
def test_group_anagrams(strings, expected):
    assert expected == group_anagrams(strings)
    
    
