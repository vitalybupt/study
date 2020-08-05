from functools import partial

def foo(a, b, c):
    print(a,b,c)

too = partial(foo, 1)
too(2,3)

tee = partial(foo, 1, 2)
tee(3)


taa = partial(foo, 2, 3)
taa(1)

tbb = partial(foo, c=1)
tbb(1,5)

'''
tcc = partial(foo, b=1)
tcc(1,5)
'''

def foos(*args):
    for i in args:
        print i

        
def kfoo(**kwargs):
    for i in kwargs.items():
        print(i)

kfoo(a=1, b=2)        
tcc = partial(kfoo, b=1)
tcc(1,5)    

def kfoos(a,b,*args,**kwargs):
    print("stand positional argument a:", a)
    print("stand positional argument b:", b)
    for i, arg in enumerate(args):
        print("extra positional argument, position:", i, " value:", arg)
    for i in kwargs.items():
        print("keyword argument key:",i[0], " value:", i[1])
kfoos(1,2,3,d=1)        
