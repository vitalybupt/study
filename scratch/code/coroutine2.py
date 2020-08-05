import time
def coroutine(func):
    def wrapper(*args, **kwargs):
        f=func(*args, **kwargs)
        next(f)
        return f
    return wrapper

def follow(file, target):
    with open(file, 'r') as f:
        f.seek(0, 2)
        while(True):
            l = f.readline()
            if(not l):
                time.sleep(0.1)
                continue
            target.send(l)

@coroutine            
def grep(pattern, target):
    while(True):
        line = (yield)
        if pattern in line:
            target.send(line)


@coroutine
def printer():
    while True:
        line = (yield)
        print(line)

follow("test", grep('python', printer()))

