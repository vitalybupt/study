#!/usr/bin/env python

from sys import stdout
from time import sleep
import sys
import time

from sys import stdin
import select

for x in range(1, 2):
    messages = [
        #'announce route 100.10.0.0/24 next-hop self',
        #'announce route 200.20.0.0/24 next-hop self'
    ]
    for y in range(1, 10):
        for o in range(1, 10):
                z = 'announce route %d.%d.%d.0/24 next-hop self' % (x, y,o)
                sys.stdout.write(z + '\n')
                sys.stdout.flush()
                #messages.append(z)

#print list
sleep(5)

#Iterate through messages
#for message in messages:
#    stdout.write( message + '\n')
#    stdout.flush()
#    sleep(1)

#while messages:
#    msg = messages.pop(0)
#    if isinstance(msg, str):
#        sys.stdout.write(msg + '\n')
#        sys.stdout.flush()


#Loop endlessly to allow ExaBGP to continue running

