import subprocess
import sys

proc = subprocess.Popen(["python3", "childprocess2.py"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)

while proc.returncode is None:
    proc.stdin.write(bytes("%s" % "input from parent\n", 'ascii'))
    proc.stdin.flush()
    output = proc.stdout.read()
    for l in output:
        print(l)
        continue
    proc.poll()
