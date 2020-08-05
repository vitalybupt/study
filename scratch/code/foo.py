from task import Task

def coroutine(func):
    def wrapper(*args, **kwargs):
        f=func(*args, **kwargs)
        next(f)
        return f
    return wrapper

#@coroutine
def goo():
    print("run 1")
    yield
    print("run 2")
    yield

def foo():
    print("run")
    return True
print(type(foo))
print(type(foo()))
print(type(goo))
print(type(goo()))
t = Task(goo())
t.run()
t.run()
