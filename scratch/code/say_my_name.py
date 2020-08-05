#!/usr/bin/env python3
# say_my_name.py
import sys
import time
sys.stdout.write("what's your name?\n")
sys.stdout.flush()

'''
while True:
    for name in iter(sys.stdin.readline, ''):
        name = name[:-1]
        if name == "exit":
            sys.stdout.write("receive exit signal\n")
            exit(0)
        sys.stdout.write("Well how do you do {0}?\n".format(name))
        sys.stdout.write("what's your name?\n")
        sys.stdout.flush()
'''

for name in sys.stdin:
    name = name[:-1]
    if name == "exit":
        sys.stdout.write("receive exit signal\n")
        break
    sys.stdout.write("Well how do you do {0}?\n".format(name))
    sys.stdout.write("what's your name?\n")
    sys.stdout.flush()

sys.stdout.write("exit subprocess say_my_name.\r\n")
sys.stdout.flush()
