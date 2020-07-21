import time
import random

def test_highest_tower():
    class block:
        h = None
        w = None
        l = None
        def __init__(self, l, w, h):
            self.h = h
            self.w = w
            self.l = l
        def display(self):
            print("block {",self.h,":",self.w,":",self.l)
        def larger(self, other):
            return (other is None) or self.h > other.h and self.w > other.w and self.l > other.l
    def sort_block(blocks):
        return sorted(blocks, key=lambda x: x.h, reverse=True)
    def create_blocks():
        random.seed(time.time())
        blocks = []
        for i in range(100):
            l = random.randint(3,30)
            w = random.randint(3,30)
            h = random.randint(3,30)
            blocks.append(block(l,w,h))
        return sort_block(blocks)
        
    def highest_tower_2(blocks, cur, prev):
        if(len(blocks) == 0):
            return 0
        next = blocks[0]
        #height without current block
        h1 = highest_tower_2(blocks[1:], next, prev)
        #height with current block
        if(prev is None or prev.larger(cur)):
            h2 = highest_tower_2(blocks[1:], next, cur)
            h2 += cur.h
            if(h2 > h1):
                h1 = h2
        
        return h1

    blocks = create_blocks()
    print(highest_tower_2(blocks[1:], blocks[0], None))

    def highest_tower(blocks, bottom, cache):
        highest = 0
        for index, next_bottom in [ (index,block) for index, block in enumerate(blocks) if block.larger(bottom) ]:
            if(cache[next_bottom] is None):
                height = next_bottom.h
                height += highest_tower(blocks[index:], next_bottom, cache)
                if (bottom is not None):
                    height += bottom.h
                cache[next_bottom] = height
                if(height>highest):
                    highest = height
            elif (cache[next_bottom] > highest):
                highest = cache[next_bottom]
        return highest

    cache = {x:None for x in blocks}
    print(highest_tower(blocks, None, cache))

test_highest_tower()


