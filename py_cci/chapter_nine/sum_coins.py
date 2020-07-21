#!/usr/bin/env python3

def sum_coins(cur, rem, count, way_map):
    if(count in way_map[cur].keys()):
        return way_map[cur][count]
    if(count < 0):
        way_map[cur][count] = 0
        return 0
    if(count == 0):
        way_map[cur][count] = 1
        return 1
    if(len(rem) == 0):
        if(count%cur == 0):
            way_map[cur][count] = 1
            return 1
        else:
            way_map[cur][count] = 0
            return 0
    dict = {}
    ways = 0
    for i in [x for x in range(count//cur+1)]:
        ways += sum_coins(rem[0], rem[1:], count-i*cur, way_map)
    way_map[cur][count] = ways
    return ways

way_map={1:{}, 5:{}, 10:{}, 25:{}}

print(sum_coins(25, [10, 5, 1], 5000, way_map))
    
    


