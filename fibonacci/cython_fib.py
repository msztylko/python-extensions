import sys

from cython_fib import fib

if __name__ == '__main__':
    for line in sys.stdin:
        n = int(line.split()[0])
        print(f"{n}\t{fib(n)}")
