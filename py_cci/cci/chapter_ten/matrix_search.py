# -*- coding: utf-8 -*-
"""
搜索矩阵：
15  20  25  40   85
20  25  38  60   95
30  55  70  95  105
40  80  90 100  120
"""
import pytest
from collections import namedtuple

dimention = namedtuple("dimention", ["start","end"])

def matrix_binary_search(matrix, target, rows, cols, vertical):
    if(vertical):
        if(rows.start > rows.end):
            return None
        mid = (rows.start + rows.end) // 2
        value = matrix[mid][cols.start]
        if(value == target):
            return (mid, cols.start)
        elif(value > target):
            return matrix_binary_search(matrix, target, dimention(rows.start, mid-1), cols, True)
        else:
            return matrix_binary_search(matrix, target, dimention(mid+1, rows.end), cols, True)
    else:
        if(cols.start > cols.end):
            return None
        mid = (cols.start + cols.end) // 2
        value = matrix[rows.start][mid]
        if(value == target):
            return (rows.start, mid)
        elif(value > target):
            return matrix_binary_search(matrix, target, rows, dimention(cols.start, mid-1), False)
        else:
            return matrix_binary_search(matrix, target, rows, dimention(mid+1, cols.end), False)
    return

def matrix_search(matrix, target, rows, cols):
    if matrix is None:
        return None
    if(rows.end == rows.start):
        return matrix_binary_search(matrix, target,rows, cols, False)
    elif(cols.end == cols.start):
        return matrix_binary_search(matrix, target,rows, cols, True)
    return (2,1)
    
matrix = [[15,20,25,40,85], [20,35,38,60,95], [30,55,70,95,105], [40.80,90,100,120]]

@pytest.mark.parametrize("matrix, target, result", [
    (matrix, 55, (2,1))
])
def test_matrix_search(matrix, target, result):
    assert matrix_search(matrix, target, dimention(2,2), dimention(0, 4)) == result
    assert matrix_search(matrix, target, dimention(0,3), dimention(1,1)) == result
