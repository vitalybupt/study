#!/usr/bin/env python3
#run_say_my_ name.py
import argparse
import subprocess
import signal
import random
import sys
import os
from time import sleep
from functools import partial

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

    def disable(self):
        self.HEADER = ''
        self.OKBLUE = ''
        self.OKGREEN = ''
        self.WARNING = ''
        self.FAIL = ''
        self.ENDC = ''

def gen_name():
    names = ['matthew', 'mark', 'john', 'marco', 'david', 'oliver', 'robin']
    while True:
        yield random.sample(names, 1)[0]


def signal_handler(sig, frame, proc):
    if(sig == signal.SIGINT):
        print("you input ctrl-c, exit\n")
        proc.stdin.write("exit\n")
        proc.stdin.flush()
        proc.wait()
        exit(0)
    else:
        print("receive signal " + str(sig))

def run_say_my_name():
    proc = subprocess.Popen(["python3", "say_my_name.py"], bufsize=1,
                            stdin=subprocess.PIPE, stdout=subprocess.PIPE,  stderr=subprocess.STDOUT, universal_newlines=True)
    prompt = proc.stdout.readline()
    print(prompt)
    name = gen_name()
    signal.signal(signal.SIGINT, partial(signal_handler, proc=proc))

    while proc.returncode is None:
        try:
            proc.stdin.write(next(name)+'\n')
            proc.stdin.flush()
            for _ in range(2):
                reply = proc.stdout.readline()
                print(reply)
            sleep(1)
            proc.poll()
        except Exception as e:
            exc_type, exc_obj, exc_tb = sys.exc_info()
            fname = os.path.split(exc_tb.tb_frame.f_code.co_filename)[1]
            print("Opps!", e.__class__, "occurred, with error message:\n!!!")
            print(f"{bcolors.FAIL}%s{bcolors.ENDC}\n" % str(e) )
            print(f"{bcolors.FAIL}in file %s, line %s{bcolors.ENDC}\n!!!" % (str(fname), str(exc_tb.tb_lineno)))
            proc.kill()
            break
    
    proc.wait()

def run_sing_a_song():
    
    return
        
if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('case', nargs='?', choices=["say_my_name", "sing_a_song"], default="say_my_name", help="choose the case you like to run")
    nc = parser.parse_args()
    if(nc.case == "say_my_name"):
        run_say_my_name()
    elif(nc.case == "sing_a_song"):
        run_sing_a_song()
    print("end parent process\r\n")


