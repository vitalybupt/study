import time

# follow -> grep ->print
def coroutine(func):
    def wrapper(*args, **kwargs):
        f=func(*args, **kwargs)
        next(f)
        return f
    return wrapper

# 1. generator style
class generator_pipeline:
    def follow(self, file):
        with open(file, 'r') as f:
            f.seek(0, 2)
            while(True):
                l = f.readline()
                if(not l):
                    time.sleep(0.1)
                    continue
                yield l
    def grep(self, pattern, lines):
        for l in lines:
            if pattern in l:
                yield l
    def test(self):
        # there are two subroutines: grep and follow
        # follow is passed to grep as parameters
        g = self.grep("python", self.follow("test"))
        for l in g:
            print(l)
t = generator_pipeline()
t.test()

# 2. coroutine style
class coroutine_pipeline:
    def follow(self, file):
        with open(file, 'r') as f:
            f.seek(0, 2)
            while(True):
                l = f.readline()
                if(not l):
                    time.sleep(0.1)
                    continue
                    yield l          
    @coroutine                    
    def grep(self, pattern):
        while(True):
            l = (yield)
            if(l is not None and  pattern in l):
                yield(l)
    @coroutine
    def count(self):
        while(True):
            l = (yield)
            if(l is not None):
                return
    def test(self):
        f = self.follow("test")
        g = self.grep("python")
        for l in f:
            g.send(l)
    
