"""
1. 分解问题
因为运算符本身没有优先级，可以简化为只有一种运算符
expr = 0&0&0&0&0
1.1
先从最简单的情况，只加一对括号开始考虑：
如果没有括号，那么运算按从左向右的顺序。
加上括号，会改变右侧运算式的运算顺序，相当于把运算式分解成了两个部分：
expr = (0&0)&(0&0&0)
那么按照括号加的位置，可以将等式分为不同的四种情况：
expr = (0)&(0&0&0&0)
      +(0&0)&(0&0&0)
      +(0&0&0)&(0&0)
      +(0&0&0&0)&(0)
      +(0&0&0&0&0)
   
1.2
可以通过观察，认知，运算式的左右部分仍是等式，我们把问题分解为其左右等式如何得到预期的结果。
2. 推导
2.1 expr=sub_expr-1|sub_expr-1|...|sub_expr-n; target = true
    sub_expr = left(op)right
    
count(expr, t) = _count(sub_expr-1, t)
                +_count(sub_expr-2, t)
                ...
                +_count(sub_expr-n, t)

2.2 sub_expr 结果为t的组合数可以用函数 _count(sub_expr, t)来计算：
sub_expr = left ^ right:
_count(left^right) = count(left, t) * count(right, f) + count(left, f) * count(right, t)

sub_expr = left & right:
_count(left&right) = count(left, t) * count(right, t)

sub_expr = left | right:
_count(left|right) = count(left, t) * count(right, t) + count(left, t) * count(right, f) + count(left, t) * count(right, f)

得到了迭代的表达式。

2.3 target = f
_count(left ^ right, t) + _count(left ^ right,  f) = 
count(left, t) * count(right, f) + count(left, f) * count(right, t)
+count(left, t) * count(right, t) + count(left, f) * count(right, f)
= {count(left, t) + count(left, f)} * {count(right, t) * count(right, f)}

total(expr) = count(expr, t) + count(expr, f); 
可以简单的推定, total(expr) 应该是一个表达式所有可能的组合，其值应该只和表达式的长度有关。
这个值的大小是：假设expr 包含的数字个数为n:
total(expr) = (2n)!/((n+1! * n!)

所以
_count(left(op)right, t) + _count(left(op)right, f) = total(left) + total(right)

_count(left(op)right, f) = total(left) + total(right) - _count(left(op)right, t)

3. 设计
count(expr, target)
3.1. 终止条件

if(len(expr) == 1):
if(expr == target): return 1 else return 0

3.2. for sub_expr in expr:
  if(op(sub_expr)== ^):
     tmp = count(left, t) * count(right, f) + count(left, f) * count(right, t)
     if(target == t)
        sum += tmp
     else 
        tmp = total(left) + total(right) - tmp
        sum += tmp
  if(op(sub_expr)== &):
     tmp = count(left, t) * count(right, t)
     if(target == t)
        sum += tmp
     else 
        tmp = total(left) + total(right) - tmp
        sum += tmp
  if(op(sub_expr) == |):
     tmp = count(left, t) * count(right, t) + count(left, t) * count(right, f) + count(left, t) * count(right, f)
     if(target == t)
        sum += tmp
     else 
        tmp = total(left) + total(right) - tmp
        sum += tmp   
   
return sum


4. 辅助函数
4.1 get_sub_expr(expr): 
generator, 从一个expr 里遍历产生所有的sub_expr。
返回值：namedtuple: sub_expr = namedtuple("sub_expor", ["left", "op", "right"])
4.2 total(expr):
total(expr) = (2n)!/((n+1! * n!)

5. 优化
将count(expr, target)的结果存在dict里，进入前先查找dict。
count(expr, target, maps):
if(maps[t+expr]):
return map[t+expr]

"""

def count(expr, target, map):
    if(len(expr) <= 0):
        return 0
    elif(len(expr) = 1):
        if(expr == target):
            return 1
        else:
            return 0
        
    for sub_expr in get_sub_expr(expr):
        if(sub_expr.op == '^'):
            tmp = count(sub_expr.left, True) * count(sub_expr.right, False) + count(sub_expr.left, False) * count(sub_expr.right, True)
        elif(sub_expr.op == '&'):
            tmp = count(sub_expr.left, True) * count(sub_expr.right, True)
        elif(sub_expr.op == '|'):
            tmp = count(sub_expr.left, True) * count(sub_expr.right, True) + count(sub_expr.left, True) * count(sub_expr.right, False) + count(sub_expr.left, True) * count(sub_expr.right, False)
        if(target == True):
            sum += tmp
        else:
            lambda n: (2n)
           total = get_total((len(sub_expr.left) + 1)/2) + get_total((len(sub_expr.left) + 1)/2)
           tmp = total - tmp
           sum += tmp
    return num
