"""
1. �ֽ�����
��Ϊ���������û�����ȼ������Լ�Ϊֻ��һ�������
expr = 0&0&0&0&0
1.1
�ȴ���򵥵������ֻ��һ�����ſ�ʼ���ǣ�
���û�����ţ���ô���㰴�������ҵ�˳��
�������ţ���ı��Ҳ�����ʽ������˳���൱�ڰ�����ʽ�ֽ�����������֣�
expr = (0&0)&(0&0&0)
��ô�������żӵ�λ�ã����Խ���ʽ��Ϊ��ͬ�����������
expr = (0)&(0&0&0&0)
      +(0&0)&(0&0&0)
      +(0&0&0)&(0&0)
      +(0&0&0&0)&(0)
      +(0&0&0&0&0)
   
1.2
����ͨ���۲죬��֪������ʽ�����Ҳ������ǵ�ʽ�����ǰ�����ֽ�Ϊ�����ҵ�ʽ��εõ�Ԥ�ڵĽ����
2. �Ƶ�
2.1 expr=sub_expr-1|sub_expr-1|...|sub_expr-n; target = true
    sub_expr = left(op)right
    
count(expr, t) = _count(sub_expr-1, t)
                +_count(sub_expr-2, t)
                ...
                +_count(sub_expr-n, t)

2.2 sub_expr ���Ϊt������������ú��� _count(sub_expr, t)�����㣺
sub_expr = left ^ right:
_count(left^right) = count(left, t) * count(right, f) + count(left, f) * count(right, t)

sub_expr = left & right:
_count(left&right) = count(left, t) * count(right, t)

sub_expr = left | right:
_count(left|right) = count(left, t) * count(right, t) + count(left, t) * count(right, f) + count(left, t) * count(right, f)

�õ��˵����ı��ʽ��

2.3 target = f
_count(left ^ right, t) + _count(left ^ right,  f) = 
count(left, t) * count(right, f) + count(left, f) * count(right, t)
+count(left, t) * count(right, t) + count(left, f) * count(right, f)
= {count(left, t) + count(left, f)} * {count(right, t) * count(right, f)}

total(expr) = count(expr, t) + count(expr, f); 
���Լ򵥵��ƶ�, total(expr) Ӧ����һ�����ʽ���п��ܵ���ϣ���ֵӦ��ֻ�ͱ��ʽ�ĳ����йء�
���ֵ�Ĵ�С�ǣ�����expr ���������ָ���Ϊn:
total(expr) = (2n)!/((n+1! * n!)

����
_count(left(op)right, t) + _count(left(op)right, f) = total(left) + total(right)

_count(left(op)right, f) = total(left) + total(right) - _count(left(op)right, t)

3. ���
count(expr, target)
3.1. ��ֹ����

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


4. ��������
4.1 get_sub_expr(expr): 
generator, ��һ��expr ������������е�sub_expr��
����ֵ��namedtuple: sub_expr = namedtuple("sub_expor", ["left", "op", "right"])
4.2 total(expr):
total(expr) = (2n)!/((n+1! * n!)

5. �Ż�
��count(expr, target)�Ľ������dict�����ǰ�Ȳ���dict��
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
