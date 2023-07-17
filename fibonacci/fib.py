import sys

def fib(n):
    if n < 2:
        return n
    else:
        return fib(n-1) + fib(n-2)

if __name__ == '__main__':
    for line in sys.stdin:
        n = int(line.split()[0])
        print(f"{n}\t{fib(n)}")
