#!/usr/bin/env python3
def check(row, col, col_set):
    if(col in col_set):
        return False
    for r in [r for r in range(row)]:
        if(abs(row - r) == abs(col_set[r] - col)):
            return False
    return True

def find_pos(row, col_set, result):
    if(row == 8):
        result.append(col_set)
        return
    for col in [col for col in range(8) if check(row, col, col_set)]:
        new_col_set = col_set.copy()
        new_col_set[row] = col
        find_pos(row+1, new_col_set, result)

def test_eight_queens():
    result =[]
    find_pos(0, [-1]*8, result)
    print(result)


    
    
