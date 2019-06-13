import sys

if len(sys.argv)!=2:
    exit(-1)

file = sys.argv[1]
with open(file) as f:
    for line in f.readlines():
        if '>' not in line:
            print(line.replace('\n',''),end='')