from collections import namedtuple
POI = namedtuple("POI", "x y")

def check_poi(x, y):
    for pixel in range(x, x+100):
        if getColor(pixel, y) != RED:
            return False
    for pixel in range(y, y+30):
        if getColor(x, pixel) != RED:
            return False
    return True

def get_poi(x_start, y_start, x_end, y_end):
    if(x_end-x_start < 100 or y_end - y_start < 30):
        return
    for x in range(x_start, x_end-100):
        for y in range(y_start, y_end-30):
            if(getColor(x, y) == RED):
                if(check_poi(x,y) == False):
                    continue
            #find POI    
            poi = {POI(x,y)}
            if(x_end - x > 200):
                poi += get_poi(x + 100, y, x_end, y+30)
            if(y_end - y > 60):
                poi += get_poi(x_start, y+30, x_end, y_end):
            return poi
    return None
